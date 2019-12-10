#include "builtin.hpp"
#include "math.hpp"
#include "vri.hpp"

namespace __vri__ {

str *const_0, *const_1, *const_2, *const_3, *const_4, *const_5, *const_6, *const_7;


str *__name__, *byte;
list<__ss_int> *dadosBinarios, *saidaPGM, *saidaPGM_NA;
__ss_int i, i_raio, j, k, res;
double res_1, res_2;
file *raw;


str * default_0;
str * default_1;
str * default_2;
str * default_3;


void *pgmwrite(list<__ss_int> *_list, __ss_int width, __ss_int height, str *filename, __ss_int maxVal, str *magicNum) {
    __ss_int __0, __1, __2, __3, i, j;
    file *f;

    f = open(filename, const_0);
    f->write((magicNum)->__add__(const_1));
    f->write(__add_strs(4, __str(width), const_2, __str(height), const_1));
    f->write((__str(maxVal))->__add__(const_1));

    FAST_FOR(i,0,height,1,0,1)

        FAST_FOR(j,0,width,1,2,3)
            f->write((__str(_list->__getfast__(((i*width)+j))))->__add__(const_2));
        END_FOR

        f->write(const_1);
    END_FOR

    f->close();
    return NULL;
}

void *pgmwrite2(list<__ss_int> *_list, __ss_int width, __ss_int height, str *filename, __ss_int maxVal, str *magicNum) {
    __ss_int __4, __5, __6, __7, i, j;
    file *f;

    f = open(filename, const_0);
    f->write((magicNum)->__add__(const_1));
    f->write(__add_strs(4, __str(width), const_2, __str(height), const_1));
    f->write((__str(maxVal))->__add__(const_1));

    FAST_FOR(i,0,height,1,4,5)

        FAST_FOR(j,0,width,1,6,7)
            f->write((__str(_list->__getfast__(((i*width)+j))))->__add__(const_2));
        END_FOR

        f->write(const_1);
    END_FOR

    f->close();
    return NULL;
}

__ss_int acesso(list<__ss_int> *vetor, __ss_int i, __ss_int j, __ss_int k) {
    
    return vetor->__getfast__((((k*65536)+(j*256))+i));
}

tuple2<double, double> *simpson(lambda1 f, double a, double b) {
    double aux, c, erro, fa, fb, fc, h, resultado, sAB, sAC, sCB;

    h = (b-a);
    c = ((a+b)/2.0);
    fa = f(a);
    fb = f(b);
    fc = f(c);
    sAB = ((h/6.0)*((fb+(4*fc))+fa));
    h = (c-a);
    aux = c;
    c = ((a+c)/2.0);
    sAC = ((h/6.0)*((fc+(4*f(c)))+fa));
    c = aux;
    h = (b-c);
    c = ((b+c)/2.0);
    sCB = ((h/6.0)*((fb+(4*f(c)))+fc));
    erro = (__abs(((sAB-sAC)-sCB))/15.0);
    resultado = ((sAC+sCB)-erro);
    return (new tuple2<double, double>(2,erro,resultado));
}

double simpsonNaoAdaptativo(lambda0 f, __ss_int a, double b, double h) {
    double fdir, fesq, n, soma;
    __ss_int __8, __9, i;

    n = ((b-a)/h);
    soma = ((double)(0));
    fesq = 0.0;
    fdir = 0.0;

    FAST_FOR(i,0,__int((n-1)),1,8,9)
        fesq = fdir;
        fdir = f((a+(h*(i+1))));
        soma = (soma+((fesq+(4*f(((a+(h*i))+(h/2)))))+fdir));
    END_FOR

    return soma;
}

double simpsonAdaptativo(lambda0 f, double a, double b, double tol) {
    tuple2<double, double> *__10;
    double c, erro, resultado;

    c = ((a+b)/2.0);
    __10 = simpson(((lambda1)(f)), a, b);
    erro = __10->__getfirst__();
    resultado = __10->__getsecond__();
    if ((tol>erro)) {
        return resultado;
    }
    else {
        return (simpsonAdaptativo(f, a, c, (tol/2.0))+simpsonAdaptativo(((lambda0)(f)), c, b, (tol/2.0)));
    }
    return 0;
}

double opacidade(double s) {
    double dt, dt1, dt2;

    dt1 = (acesso(dadosBinarios, i_raio, __int(s), k)/255.0);
    try {
        dt2 = (acesso(dadosBinarios, i_raio, (__int(s)+1), k)/255.0);
        dt = ((dt1+dt2)/2.0);
    } catch (Exception *) {
        dt = dt1;
    }
    if ((dt<0.3)) {
        return ((double)(0));
    }
    else {
        return ((0.05*dt)-0.015);
    }
    return 0;
}

double funcaoRenderizacaoVolumetrica(double t) {
    double integral_interna;

    integral_interna = (-simpsonAdaptativo(opacidade, ((double)(0)), t, 0.01));
    return (opacidade(t)*__math__::exp(integral_interna));
}

double integralRenderizacaoVolumetrica(__ss_int s) {
    
    return (simpsonAdaptativo(((lambda0)(funcaoRenderizacaoVolumetrica)), ((double)(0)), ((double)(s)), 0.01)/3.92285497929);
}

double funcaoRenderizacaoVolumetrica2(double t) {
    double integral_interna;

    integral_interna = (-simpsonNaoAdaptativo(opacidade, 0, t, 4.5));
    return (opacidade(t)*__math__::exp(integral_interna));
}

double integralRenderizacaoVolumetrica2(__ss_int s) {
    
    return (simpsonNaoAdaptativo(((lambda0)(funcaoRenderizacaoVolumetrica2)), 0, ((double)(s)), 4.5)/3.92285497929);
}

void __init() {
    const_0 = __char_cache[119];;
    const_1 = __char_cache[10];;
    const_2 = __char_cache[32];;
    const_3 = new str("output.pgm");
    const_4 = new str("P2");
    const_5 = new str("output2.pgm");
    const_6 = new str("vridados-head-8bit.raw");
    const_7 = new str("rb");

    __name__ = new str("__main__");

    default_0 = const_3;
    default_1 = const_4;
    default_2 = const_5;
    default_3 = const_4;
    dadosBinarios = (new list<__ss_int>());
    saidaPGM = (new list<__ss_int>());
    saidaPGM_NA = (new list<__ss_int>());
    raw = open(const_6, const_7);
    byte = raw->read(1);

    while (___bool(byte)) {
        dadosBinarios->append(ord(byte));
        byte = raw->read(1);
    }
    raw->close();
    i = 0;
    j = 0;
    k = 0;

    while ((k<99)) {
        i = 0;

        while ((i<256)) {
            i_raio = i;
            res_1 = integralRenderizacaoVolumetrica(255);
            i_raio = (i_raio+1);
            res_2 = integralRenderizacaoVolumetrica(255);
            i = (i+2);
            res = __int(((255.0*(res_1+res_2))/2.0));
            saidaPGM->append(res);
        }
        k = (k+1);
    }
    pgmwrite(saidaPGM, 128, 99, default_0, 255, default_1);
    i = 0;
    j = 0;
    k = 0;

    while ((k<99)) {
        i = 0;

        while ((i<256)) {
            i_raio = i;
            res_1 = integralRenderizacaoVolumetrica2(255);
            i_raio = (i_raio+1);
            res_2 = integralRenderizacaoVolumetrica2(255);
            i = (i+2);
            res = __int(((255.0*(res_1+res_2))/2.0));
            saidaPGM_NA->append(res);
        }
        k = (k+1);
    }
    pgmwrite2(saidaPGM_NA, 128, 99, default_2, 255, default_3);
}

} // module namespace

int main(int, char **) {
    __shedskin__::__init();
    __math__::__init();
    __shedskin__::__start(__vri__::__init);
}
