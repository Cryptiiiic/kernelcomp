#include <stdio.h>
#include <img4tool/img4tool.hpp>
#include <img4tool/ASN1DERElement.hpp>

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        fprintf(stderr, "%s kernel.patched kernel.out kpp.bin\n", argv[0]);
        fprintf(stderr, "\n(kpp is required with a9 and lower)\n");
        exit(1);
    }
    FILE *f = fopen(argv[1], "rb");
    fseek(f, 0, SEEK_END);
    char *kernel_patched = nullptr;
    size_t kernel_patched_size = 0;
    kernel_patched_size = ftell(f);
    fseek(f, 0, SEEK_SET);
    kernel_patched = (char*)malloc(kernel_patched_size);
    if(fread(kernel_patched, 1, kernel_patched_size, f) == kernel_patched_size) printf("reading kernel...\n");
    tihmstar::img4tool::ASN1DERElement kernel_im4p = tihmstar::img4tool::getEmptyIM4PContainer("rkrn", "KernelCacheBuilder-pwned");
    if(!kernel_im4p.size())
    {
        fprintf(stderr, "ERROR: kernel_im4p getEmptyIMG4Container\n");
        exit(1);
    }
    printf("compressing kernel...\n");
    char *kpp = NULL;
    size_t kpp_size = 0;
    FILE *kpp_file = NULL;
    if(argc > 3)
    {
        kpp_file = fopen(argv[3], "rb");
        fseek(kpp_file, 0, SEEK_END);
        kpp_size = ftell(kpp_file);
        fseek(kpp_file, 0, SEEK_SET);
        kpp = (char*)malloc(kpp_size);
        if(fread(kpp, 1, kpp_size, kpp_file) == kpp_size) printf("reading kpp...\n");
    }
    kernel_im4p = tihmstar::img4tool::appendPayloadToIM4P(kernel_im4p, kernel_patched, kernel_patched_size, "complzss", kpp, kpp_size);
    printf("done\n");
    if(!kernel_im4p.size())
    {
        fprintf(stderr, "ERROR: kernel_im4p appendPayloadToIM4P\n");
        exit(1);
    }
    fclose(f);
    if(kernel_im4p.size() >= kernel_patched_size)
    {
        fprintf(stderr, "ERROR: compression failed\n");
        exit(1);
    }
    f = fopen(argv[2], "wb");
    kernel_im4p = kernel_im4p[3];
    fwrite(kernel_im4p.payload(), 1, kernel_im4p.payloadSize(), f);
    fclose(f);
    return 0;
}