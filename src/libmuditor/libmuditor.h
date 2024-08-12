#ifndef MUDITOR
#define MUDITOR

#include <math.h>
#include <complex.h>
#include <sys/types.h>
#include "../../raylib-5.0_linux_amd64/include/raylib.h"

/*Defines */
#define ARRAY_LEN(x) sizeof(x)/sizeof(x[0])
#define MYCOLOR CLITERAL(Color){22 ,22 ,22 ,1}
#define WAVES_COLOR CLITERAL(Color) {10, 217, 89,1}
#define SAMPLES_NO (256)

/*Typedefs*/
typedef struct {
    float left;
    float right;

}Frame ;

typedef float complex cplx;

typedef struct {
    Music music
}Muditor;


const char *libmuditor_name = "libmuditor.so";
float in[SAMPLES_NO] = {0};
cplx out[SAMPLES_NO] = {0};
float max_amp;


/*-----------------------------------------------------------------------*/
typedef void (*fp_muditor_init)(Muditor*);
typedef void (*fp_muditor_renderframe)(Muditor*);
/*-----------------------------------------------------------------------*/
void fft(float in[], cplx out[], size_t step, size_t N);
void audioCallBack(void *bufferData, unsigned int frames);

float ampl(cplx n){
    return sqrtf(crealf(n) * crealf(n)+ cimagf(n) * cimagf(n));
}
#endif 
