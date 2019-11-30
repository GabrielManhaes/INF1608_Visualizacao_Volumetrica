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
    for j in range(width):
      f.write(str(list[i * width + j]) + ' ')
    f.write('\n')
  f.close()


def acesso ( vetor , i , j , k ):
    return vetor[k*65536 + j*256 + i]

def simpson ( f , a , b ):

    h = b - a
    c = ( a + b ) / 2.0
    fa = f(a)
    fb = f(b)
    fc = f(c)

    sAB = ( h / 6.0 ) * ( fb + 4 * fc + fa )

    h = c - a
    aux = c
    c = ( a + c ) / 2.0
    sAC = ( h / 6.0 ) * ( fc + 4 * f(c) + fa )
    
    c = aux
    h = b - c
    c = ( b + c ) / 2.0
    sCB = ( h / 6.0 ) * ( fb + 4 * f(c) + fc )

    erro = abs( sAB - sAC - sCB ) / 15.0
    resultado = sAC + sCB - erro
    return erro, resultado


def simpsonAdaptativo ( f , a , b , tol ):

    c = ( a + b ) / 2.0
    erro, resultado = simpson( f , a , b )

    if tol > erro :
        return resultado
    else :
        return simpsonAdaptativo( f , a , c , tol / 2.0 ) + simpsonAdaptativo( f , c , b , tol / 2.0 )


def opacidade ( s ):
    dt1 = acesso( dadosBinarios , i_raio , int(s) , k ) / 255.0
    try:
        dt2 = acesso( dadosBinarios , i_raio , int(s) + 1 , k ) / 255.0
        dt = (dt1 + dt2) / 2.0
    except:
        dt = dt1

    if dt < 0.3 :
        return 0
    else :
        return 0.05 * dt - 0.015

def funcaoRenderizacaoVolumetrica( t ):
    integral_interna = -simpsonAdaptativo( opacidade , 0 , t , 0.01 ) # / 4.22555555556
    return opacidade(t) * math.exp( integral_interna )

def integralRenderizacaoVolumetrica ( s ):
    return simpsonAdaptativo ( funcaoRenderizacaoVolumetrica , 0 , s , 0.01 ) / 3.92285497929

########################################
########################################
########################################


dadosBinarios = []
saidaPGM = []
raw = open("vridados-head-8bit.raw", "rb")


byte = raw.read(1)
while byte:
    dadosBinarios.append(ord(byte))
    byte = raw.read(1)

raw.close()

i = 0
j = 0
k = 0
while k < 99:
    i = 0
    while i < 256:
        i_raio = i
        res_1 = integralRenderizacaoVolumetrica(255)
        i_raio += 1
        res_2 = integralRenderizacaoVolumetrica(255)
        i += 2
        
        res = int(255.0*(res_1+res_2)/2.)
        saidaPGM.append(res)
    k += 1

pgmwrite(saidaPGM)
