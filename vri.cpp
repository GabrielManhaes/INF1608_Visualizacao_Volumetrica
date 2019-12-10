#include "builtin.hpp"
#include "math.hpp"
#include "vri.hpp"

namespace __vri__ {

str *const_0, *const_1, *const_2, *const_3, *const_4, *const_5, *const_6, *const_7;


__ss_int i_raio, i, res, k;
double res_2, res_1;
file *raw;
list<__ss_int> *saidaPGM, *dadosBinarios;
str *__name__, *byte;

str * default_0;



void *pgmwrite(list<__ss_int> *_list, str *filename, __ss_int width, __ss_int height, __ss_int maxVal, str *magicNum) {
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

__ss_int acesso(list<__ss_int> *vetor, __ss_int i, __ss_int j, __ss_int k) {
    
    return vetor->__getfast__((((k*__ss_int(65536))+(j*__ss_int(256)))+i));
}

tuple2<double, double> *simpson(lambda0 f, double a, double b) {
    double aux, c, erro, fa, fb, fc, h, resultado, sAB, sAC, sCB;

    h = (b-a);
    c = ((a+b)/2.0);
    fa = f(a);
    fb = f(b);
    fc = f(c);
    sAB = ((h/6.0)*((fb+(__ss_int(4)*fc))+fa));
    h = (c-a);
    aux = c;
    c = ((a+c)/2.0);
    sAC = ((h/6.0)*((fc+(__ss_int(4)*f(c)))+fa));
    c = aux;
    h = (b-c);
    c = ((b+c)/2.0);
    sCB = ((h/6.0)*((fb+(__ss_int(4)*f(c)))+fc));
    erro = (__abs(((sAB-sAC)-sCB))/15.0);
    resultado = ((sAC+sCB)-erro);
    return (new tuple2<double, double>(2,erro,resultado));
}

double simpsonNaoAdaptativo(lambda2 f, __ss_int a, double b, double h) {
    double fdir, fesq, n, soma;
    __ss_int __4, __5, i;

    n = ((b-a)/h);
    soma = ((double)(__ss_int(0)));
    fesq = 0.0;
    fdir = 0.0;

    FAST_FOR(i,0,__int((n-__ss_int(1))),1,4,5)
        fesq = fdir;
        fdir = f((a+(h*(i+__ss_int(1)))));
        soma = (soma+((fesq+(__ss_int(4)*f(((a+(h*i))+(h/__ss_int(2))))))+fdir));
    END_FOR

    return soma;
}

double simpsonAdaptativo(lambda0 f, double a, double b, double tol) {
    tuple2<double, double> *__6;
    double c, erro, resultado;

    c = ((a+b)/2.0);
    __6 = simpson(f, a, b);
    erro = __6->__getfirst__();
    resultado = __6->__getsecond__();
    if ((tol>erro)) {
        return resultado;
    }
    else {
        return (simpsonAdaptativo(((lambda0)(f)), a, c, (tol/2.0))+simpsonAdaptativo(f, c, b, (tol/2.0)));
    }
    return 0;
}

double opacidade(double j) {
    double dt, dt1, dt2, ratio;
    __ss_int j_int;

    j_int = __int(j);
    ratio = (j-j_int);
    dt1 = (((__ss_int(1)-ratio)*acesso(__vri__::dadosBinarios, __vri__::i_raio, __int(j), __vri__::k))/255.0);
    dt2 = ((ratio*acesso(__vri__::dadosBinarios, __vri__::i_raio, (__int(j)+__ss_int(1)), __vri__::k))/255.0);
    dt = (dt1+dt2);
    if ((dt<0.3)) {
        return ((double)(__ss_int(0)));
    }
    else {
        return ((0.05*dt)-0.015);
    }
    return 0;
}

double funcaoRenderizacaoVolumetrica(double t) {
    double integral_interna;

    integral_interna = (-simpsonAdaptativo(opacidade, ((double)(__ss_int(0))), t, 0.001));
    return (opacidade(t)*__math__::exp(integral_interna));
}

double funcaoRenderizacaoVolumetrica2(double t) {
    double integral_interna;

    integral_interna = (-simpsonNaoAdaptativo(((lambda2)(opacidade)), __ss_int(0), t, 4.5));
    return (opacidade(t)*__math__::exp(integral_interna));
}

void __init() {
    const_0 = __char_cache[119];;
    const_1 = __char_cache[10];;
    const_2 = __char_cache[32];;
    const_3 = new str("P2");
    const_4 = new str("vridados-head-8bit.raw");
    const_5 = new str("rb");
    const_6 = new str("adaptativo.pgm");
    const_7 = new str("naoadaptativo.pgm");

    __name__ = new str("__main__");

    default_0 = const_3;
    dadosBinarios = (new list<__ss_int>());
    saidaPGM = (new list<__ss_int>());
    raw = open(const_4, const_5);
    byte = __vri__::raw->read(__ss_int(1));

    while (___bool(__vri__::byte)) {
        __vri__::dadosBinarios->append(ord(__vri__::byte));
        byte = __vri__::raw->read(__ss_int(1));
    }
    __vri__::raw->close();
    i = __ss_int(0);
    k = __ss_int(0);

    while ((__vri__::k<__ss_int(99))) {
        i = __ss_int(0);

        while ((__vri__::i<__ss_int(128))) {
            i_raio = (__ss_int(2)*__vri__::i);
            res_1 = simpsonAdaptativo(((lambda0)(funcaoRenderizacaoVolumetrica)), ((double)(__ss_int(0))), ((double)(__ss_int(254))), 0.01);
            i_raio = (__vri__::i_raio+__ss_int(1));
            res_2 = simpsonAdaptativo(((lambda0)(funcaoRenderizacaoVolumetrica)), ((double)(__ss_int(0))), ((double)(__ss_int(254))), 0.01);
            i = (__vri__::i+__ss_int(1));
            res = __int(((255.0*(__vri__::res_1+__vri__::res_2))/2.0));
            __vri__::saidaPGM->append(__vri__::res);
        }
        k = (__vri__::k+__ss_int(1));
    }
    pgmwrite(__vri__::saidaPGM, const_6, __ss_int(128), __ss_int(99), __ss_int(255), default_0);
    saidaPGM = (new list<__ss_int>());
    i = __ss_int(0);
    k = __ss_int(0);

    while ((__vri__::k<__ss_int(99))) {
        i = __ss_int(0);

        while ((__vri__::i<__ss_int(128))) {
            i_raio = (__ss_int(2)*__vri__::i);
            res_1 = simpsonNaoAdaptativo(funcaoRenderizacaoVolumetrica2, __ss_int(0), ((double)(__ss_int(254))), 4.5);
            i_raio = (__vri__::i_raio+__ss_int(1));
            res_2 = simpsonNaoAdaptativo(funcaoRenderizacaoVolumetrica2, __ss_int(0), ((double)(__ss_int(254))), 4.5);
            i = (__vri__::i+__ss_int(1));
            res = __int(((255.0*(__vri__::res_1+__vri__::res_2))/2.0));
            __vri__::saidaPGM->append(__vri__::res);
        }
        k = (__vri__::k+__ss_int(1));
    }
    pgmwrite(__vri__::saidaPGM, const_7, __ss_int(128), __ss_int(99), __ss_int(255), default_0);
}

} // module namespace

int main(int, char **) {
    __shedskin__::__init();
    __math__::__init();
    __shedskin__::__start(__vri__::__init);
}
