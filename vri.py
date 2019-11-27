import numpy as np
import math

########################################
######### FUNCOES AUXILIARES ###########
########################################

def pgmwrite( list , width = 128 , height = 99 , filename = "output.pgm" , maxVal = 255 , magicNum = 'P2' ):
  f = open(filename,'w')
  f.write(magicNum + '\n')
  f.write(str(width) + ' ' + str(height) + '\n')
  f.write(str(maxVal) + '\n')
  for i in range(height):
    count = 1
    for j in range(width):
      f.write(str(list[i * width + j]) + ' ')
      if count >= 17:
        count = 1
        f.write('\n')
      else:
        count = count + 1
    f.write('\n')
  f.close()

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
    dt = acesso( dadosBinarios , i_raio , int(math.floor(s)) , k ) / 255.0
    if dt < 0.3 :
        return 0
    else :
        return 0.05 * ( dt - 0.3 )


def integralRenderizacaoVolumetrica ( s ):
    def funcaoRenderizacaoVolumetrica( t ):
        integral_interna = -simpsonAdaptativo( opacidade , 0 , t , 0.01 )
        return opacidade(t) * np.exp( integral_interna )
    return simpsonAdaptativo ( funcaoRenderizacaoVolumetrica , 0 , s , 0.01)


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
        i_raio = 2*i
        resultado = 0
        res_1 = integralRenderizacaoVolumetrica(255)
        i_raio += 1
        resultado = 0
        res_2 = integralRenderizacaoVolumetrica(255)
        i += 1
        res = int(255*(res_1+res_2)/2)
        saidaPGM.append(res)
    k += 1

pgmwrite(saidaPGM)