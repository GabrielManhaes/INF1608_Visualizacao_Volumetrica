import math

########################################
######### FUNCOES AUXILIARES ###########
########################################

def pgmwrite( list , filename , width = 128 , height = 99 , maxVal = 255 , magicNum = 'P2' ):
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

def simpsonNaoAdaptativo (f, a, b, h):
    n = (b - a) / h
    soma = 0
    fesq = 0.0
    fdir = 0.0

    for i in range (int(n - 1)):
        fesq = fdir
        fdir = f(a + h * (i + 1))
        soma = soma + (fesq + 4*f(a + h * i + (h/2)) + fdir)
    
    return soma


def simpsonAdaptativo ( f , a , b , tol ):

    c = ( a + b ) / 2.0
    erro, resultado = simpson( f , a , b )

    if tol > erro :
        return resultado
    else :
        return simpsonAdaptativo( f , a , c , tol / 2.0 ) + simpsonAdaptativo( f , c , b , tol / 2.0 )


def opacidade ( j ):
    j_int = int(j)
    ratio = j - j_int
    dt1 = (1 - ratio) * acesso( dadosBinarios , i_raio , int(j) , k ) / 255.0
    dt2 = ratio * acesso( dadosBinarios , i_raio , int(j) + 1 , k ) / 255.0
    dt = (dt1 + dt2)

    if dt < 0.3 :
        return 0
    else :
        return 0.05 * dt - 0.015

def funcaoRenderizacaoVolumetrica( t ):
    integral_interna = -simpsonAdaptativo( opacidade , 0 , t , 0.001 )
    return opacidade(t) * math.exp( integral_interna )

def funcaoRenderizacaoVolumetrica2( t ):
    integral_interna = -simpsonNaoAdaptativo( opacidade , 0 , t , 4.5 )
    return opacidade(t) * math.exp( integral_interna )


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
k = 0
while k < 99:
    i = 0
    while i < 128:
        i_raio = 2*i
        res_1 = simpsonAdaptativo ( funcaoRenderizacaoVolumetrica , 0 , 254 , 0.001 )
        i_raio += 1
        res_2 = simpsonAdaptativo ( funcaoRenderizacaoVolumetrica , 0 , 254 , 0.001 )
        i += 1
        
        res = int(255.0*(res_1+res_2)/2.)
        saidaPGM.append(res)
    k += 1

pgmwrite(saidaPGM, "adaptativo.pgm")
saidaPGM = []

i = 0
k = 0
while k < 99:
    i = 0
    while i < 128:
        i_raio = 2*i
        res_1 = simpsonNaoAdaptativo ( funcaoRenderizacaoVolumetrica2 , 0 , 254 , 4.5 )
        i_raio += 1
        res_2 = simpsonNaoAdaptativo ( funcaoRenderizacaoVolumetrica2 , 0 , 254 , 4.5 )
        i += 1
        res = int(255.0*(res_1+res_2)/2.)
        saidaPGM.append(res)
    k += 1

pgmwrite(saidaPGM, "naoadaptativo.pgm")
