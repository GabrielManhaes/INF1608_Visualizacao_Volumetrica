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


def lerp ( v0 , v1 , step):
    return ( 1 - step ) * v0 + step * v1


def simpson ( f , a , b ):
    global resultado

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
    dt1 = acesso( dadosBinarios , i_raio , int(math.floor(s)) , k ) / 255.0

    try:
        dt2 = acesso( dadosBinarios , i_raio , int(math.floor(s)) + 1 , k ) / 255.0
    except:
        dt2 = dt1

    dt = lerp(dt1, dt2, 0.5)

    if dt < 0.3 :
        return 0
    else :
        return 0.05 * ( dt - 0.3 )

def funcaoRenderizacaoVolumetrica( t ):
    integral_interna = -simpsonAdaptativo( opacidade , 0 , t , 0.01 )
    return opacidade(t) * math.exp( integral_interna )
    
def integralRenderizacaoVolumetrica ( s ):     
    return simpsonAdaptativo ( funcaoRenderizacaoVolumetrica , 0 , s , 0.01 ) / 2.43378288501


########################################
########################################
########################################


dadosBinarios = []
saidaPGM = []
raw = open("vridados-head-8bit.raw", "rb")


byte = raw.read(1)
while byte != "":
    dadosBinarios.append(ord(byte))
    byte = raw.read(1)

raw.close()


resultado = 0
i = 0
j = 0
k = 0
maxval = 0
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
	if (res_1+res_2)/2.0 > maxval:
            maxval = (res_1+res_2)/2.0
        res = int(255.0*(res_1+res_2)/2.)
        saidaPGM.append(res)
    k += 1

pgmwrite(saidaPGM)
print(maxval)
