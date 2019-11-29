#ifndef __VRI_CPP_HPP
#define __VRI_CPP_HPP

using namespace __shedskin__;
namespace __vri_cpp__ {

extern str *const_0, *const_1, *const_2, *const_3, *const_4, *const_5, *const_6, *const_7;


typedef double (*lambda1)(double);
typedef double (*lambda0)(double);

extern __ss_int i, i_raio, j, k, res;
extern str *__name__, *byte;
extern file *raw;
extern double maxval, res_1, res_2, resultado;
extern list<__ss_int> *dadosBinarios, *saidaPGM;


extern str * default_0;
extern str * default_1;
void *pgmwrite(list<__ss_int> *_list, __ss_int width, __ss_int height, str *filename, __ss_int maxVal, str *magicNum);
__ss_int acesso(list<__ss_int> *vetor, __ss_int i, __ss_int j, __ss_int k);
double lerp(double v0, double v1, double step);
double simpson(lambda1 f, double a, double b);
double simpsonAdaptativo(lambda1 f, double a, double b, double tol);
double opacidade(double s);
double funcaoRenderizacaoVolumetrica(double t);
double integralRenderizacaoVolumetrica(__ss_int s);

} // module namespace
#endif
