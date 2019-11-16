import numpy as np
import math

########################################
######### FUNCOES AUXILIARES ###########
########################################

def acesso ( vetor , i , j , k ):
    return vetor[k*256*256 + j*256 + i]


def simpson ( f , a , b ):
    global resultado
    h = b - a
    c = ( a + b ) / 2.0
    sAB = ( h / 6.0 ) * ( f(b) + 4 * f(c) + f(a) )

    h = c - a
    aux = c
    c = ( a + c ) / 2.0
    sAC = ( h / 6.0 ) * ( f(aux) + 4 * f(c) + f(a) )
    
    c = aux
    h = b - c
    c = ( b + c ) / 2.0
    sCB = ( h / 6.0 ) * ( f(b) + 4 * f(c) + f(aux) )

    erro = abs( sAB - sAC - sCB ) / 15.0
    resultado = sAC + sCB - erro
    return erro


def simpsonAdaptativo ( f , a , b , tol ):
    global resultado
    c = ( a + b ) / 2.0
    erro = simpson( f , a , b )

    if tol > erro :
        return resultado
    else :
        return simpsonAdaptativo( f , a , c , tol / 2.0 ) + simpsonAdaptativo( f , c , b , tol / 2.0 )


def opacidade ( s ):
    dt = acesso( dadosBinarios , i , int(math.floor(s)) , k ) / 255.0
    if dt < 0.3 :
        return 0
    else :
        return 0.05 * ( dt - 0.3 )


def integralRenderizacaoVolumetrica ( s ):
    def funcaoRenderizacaoVolumetrica( s ):
        integral_interna = -simpsonAdaptativo( opacidade , 0 , s , 0.001 )
        print(opacidade(s) * np.exp( integral_interna ))
        return opacidade(s) * np.exp( integral_interna )
    return simpsonAdaptativo ( funcaoRenderizacaoVolumetrica , 0 , 255 , 0.001)


########################################
########################################
########################################


dadosBinarios = []
saidaPGM = []
raw = open("vridados-head-8bit.raw", "rb")

try:
    byte = raw.read(1)
    while byte != "":
        dadosBinarios.append(ord(byte))
        byte = raw.read(1)
finally:
    raw.close()


resultado = 0
i = 0
j = 0
k = 0

while k < 99:
    i = 0
    while i < 128:
        j = 0
        while j < 255:
            print(integralRenderizacaoVolumetrica(j))
            j += 1
        i += 1
    k += 1