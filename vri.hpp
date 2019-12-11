#ifndef __VRI_HPP
#define __VRI_HPP

using namespace __shedskin__;
namespace __vri__ {

extern str *const_0, *const_1, *const_2, *const_3, *const_4, *const_5, *const_6, *const_7;


typedef double (*lambda2)(double);
typedef double (*lambda1)(double);
typedef double (*lambda0)(double);

extern __ss_int i, i_raio, k, res;
extern str *__name__, *byte;
extern file *raw;
extern double res_1, res_2;
extern list<__ss_int> *dadosBinarios, *saidaPGM;


extern str * default_0;

void *pgmwrite(list<__ss_int> *_list, str *filename, __ss_int width, __ss_int height, __ss_int maxVal, str *magicNum);
__ss_int acesso(list<__ss_int> *vetor, __ss_int i, __ss_int j, __ss_int k);
tuple2<double, double> *simpson(lambda1 f, double a, double b);
double simpsonNaoAdaptativo(lambda0 f, __ss_int a, double b, double h);
double simpsonAdaptativo(lambda1 f, double a, double b, double tol);
double opacidade(double j);
double funcaoRenderizacaoVolumetrica(double t);
double funcaoRenderizacaoVolumetrica2(double t);

} // module namespace
#endif
