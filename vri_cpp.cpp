#include "builtin.hpp"
#include "math.hpp"
#include "vri_cpp.hpp"

namespace __vri_cpp__ {

str *const_0, *const_1, *const_2, *const_3, *const_4, *const_5, *const_6, *const_7;


__ss_int i, res, k, j, i_raio;
double resultado, maxval, res_2, res_1;
file *raw;
list<__ss_int> *saidaPGM, *dadosBinarios;
str *__name__, *byte;

str * default_0;
str * default_1;



void *pgmwrite(list<__ss_int> *_list, __ss_int width, __ss_int height, str *filename, __ss_int maxVal, str *magicNum) {
    __ss_int __0, __1, __2, __3, count, i, j;
    file *f;

    f = open(filename, const_0);
    f->write((magicNum)->__add__(const_1));
    f->write(__add_strs(4, __str(width), const_2, __str(height), const_1));
    f->write((__str(maxVal))->__add__(const_1));

    FAST_FOR(i,0,height,1,0,1)
        count = __ss_int(1);

        FAST_FOR(j,0,width,1,2,3)
            f->write((__str(_list->__getfast__(((i*width)+j))))->__add__(const_2));
            if ((count>=__ss_int(17))) {
                count = __ss_int(1);
                f->write(const_1);
            }
            else {
                count = (count+__ss_int(1));
            }
        END_FOR

        f->write(const_1);
    END_FOR

    f->close();
    return NULL;
}

__ss_int acesso(list<__ss_int> *vetor, __ss_int i, __ss_int j, __ss_int k) {
    
    return vetor->__getfast__(((((k*__ss_int(256))*__ss_int(256))+(j*__ss_int(256)))+i));
}

double lerp(double v0, double v1, double step) {
    
    return (((__ss_int(1)-step)*v0)+(step*v1));
}

double simpson(lambda1 f, double a, double b) {
    double aux, c, erro, fa, fb, fc, h, sAB, sAC, sCB;

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
    return erro;
}

double simpsonAdaptativo(lambda1 f, double a, double b, double tol) {
    double c, erro;

    c = ((a+b)/2.0);
    erro = simpson(f, a, b);
    if ((tol>erro)) {
        return __vri_cpp__::resultado;
    }
    else {
        return (simpsonAdaptativo(f, a, c, (tol/2.0))+simpsonAdaptativo(f, c, b, (tol/2.0)));
    }
    return 0;
}

double opacidade(double s) {
    double dt, dt1, dt2;

    dt1 = (acesso(__vri_cpp__::dadosBinarios, __vri_cpp__::i_raio, __int(__math__::floor(s)), __vri_cpp__::k)/255.0);
    try {
        dt2 = (acesso(__vri_cpp__::dadosBinarios, __vri_cpp__::i_raio, (__int(__math__::floor(s))+__ss_int(1)), __vri_cpp__::k)/255.0);
    } catch (Exception *) {
        dt2 = dt1;
    }
    dt = lerp(dt1, dt2, 0.5);
    if ((dt<0.3)) {
        return ((double)(__ss_int(0)));
    }
    else {
        return (0.05*(dt-0.3));
    }
    return 0;
}

double funcaoRenderizacaoVolumetrica(double t) {
    double integral_interna;

    integral_interna = (-simpsonAdaptativo(((lambda1)(opacidade)), ((double)(__ss_int(0))), t, 0.01));
    return (opacidade(t)*__math__::exp(integral_interna));
}

double integralRenderizacaoVolumetrica(__ss_int s) {
    
    return (simpsonAdaptativo(funcaoRenderizacaoVolumetrica, ((double)(__ss_int(0))), ((double)(s)), 0.01)/2.43378288501);
}

void __init() {
    const_0 = __char_cache[119];;
    const_1 = __char_cache[10];;
    const_2 = __char_cache[32];;
    const_3 = new str("output.pgm");
    const_4 = new str("P2");
    const_5 = new str("vridados-head-8bit.raw");
    const_6 = new str("rb");
    const_7 = new str("");

    __name__ = new str("__main__");

    default_0 = const_3;
    default_1 = const_4;
    dadosBinarios = (new list<__ss_int>());
    saidaPGM = (new list<__ss_int>());
    raw = open(const_5, const_6);
    byte = __vri_cpp__::raw->read(__ss_int(1));

    while (__ne(__vri_cpp__::byte, const_7)) {
        __vri_cpp__::dadosBinarios->append(ord(__vri_cpp__::byte));
        byte = __vri_cpp__::raw->read(__ss_int(1));
    }
    __vri_cpp__::raw->close();
    resultado = ((double)(__ss_int(0)));
    i = __ss_int(0);
    j = __ss_int(0);
    k = __ss_int(0);
    maxval = ((double)(__ss_int(0)));

    while ((__vri_cpp__::k<__ss_int(99))) {
        i = __ss_int(0);

        while ((__vri_cpp__::i<__ss_int(128))) {
            i_raio = (__ss_int(2)*__vri_cpp__::i);
            resultado = ((double)(__ss_int(0)));
            res_1 = integralRenderizacaoVolumetrica(__ss_int(255));
            i_raio = (__vri_cpp__::i_raio+__ss_int(1));
            resultado = ((double)(__ss_int(0)));
            res_2 = integralRenderizacaoVolumetrica(__ss_int(255));
            i = (__vri_cpp__::i+__ss_int(1));
            if ((((__vri_cpp__::res_1+__vri_cpp__::res_2)/2.0)>__vri_cpp__::maxval)) {
                maxval = ((__vri_cpp__::res_1+__vri_cpp__::res_2)/2.0);
            }
            res = __int(((255.0*(__vri_cpp__::res_1+__vri_cpp__::res_2))/2.0));
            __vri_cpp__::saidaPGM->append(__vri_cpp__::res);
        }
        k = (__vri_cpp__::k+__ss_int(1));
    }
    pgmwrite(__vri_cpp__::saidaPGM, __ss_int(128), __ss_int(99), default_0, __ss_int(255), default_1);
    print2(NULL,0,1, ___box(__vri_cpp__::maxval));
}

} // module namespace

int main(int, char **) {
    __shedskin__::__init();
    __math__::__init();
    __shedskin__::__start(__vri_cpp__::__init);
}
