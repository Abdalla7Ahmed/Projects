
#include<stdio.h>


extern unsigned int _stack_top;
extern int main(void);
void Reset_Handler(void);
void Default_Handler()
{
    Reset_Handler();
}

void NMI_Handler()__attribute__((weak,alias ("Default_Handler")));;
void H_fault_Handler()__attribute__((weak,alias ("Default_Handler")));;
void MM_fault_Handler()__attribute__((weak,alias ("Default_Handler")));;
void Bus_fault()__attribute__((weak,alias ("Default_Handler")));;
void Usage_fault_Handler()__attribute__((weak,alias ("Default_Handler")));;

unsigned int Vectors[] __attribute__((section(".Vectors")))={
(unsigned int)         &_stack_top,
(unsigned int)         &Reset_Handler,
(unsigned int)         &NMI_Handler,
(unsigned int)         &H_fault_Handler,
(unsigned int)         &MM_fault_Handler,
(unsigned int)         &Bus_fault,
(unsigned int)         &Usage_fault_Handler
};
extern unsigned int  _E_text;
extern unsigned int  _S_DATA;
extern unsigned int  _E_DATA;
extern unsigned int  _S_bss;
extern unsigned int  _E_bss;

void Reset_Handler(void)
{
    // copy data from ROM to RAM
    unsigned int  DATA_size = (unsigned char *)&_E_DATA - (unsigned char *)&_S_DATA;
    unsigned char  * p_src=(unsigned char *)&_E_text;
    unsigned char * p_dst=(unsigned char *)&_S_DATA;
    unsigned int  i;
    for( i=0;i<DATA_size;i++)
    {
        *((unsigned char *)p_dst++)=*((unsigned char *)p_src++);
    }

    // init the bss sectoin with zero
    
    unsigned int bss_size = (unsigned char *)&_E_bss - (unsigned char *)&_S_bss; 
    p_dst=(unsigned char *)&_S_bss;

    for(i=0;i<bss_size;i++)
    {
        *((unsigned char *)p_dst++)=(unsigned char)0;
    }    

    // jump to main 

    main();
}
