# Visualização Volumétrica

### Para gerar o .cpp e executável a partir do vri.py

- Instalar o shedskin e suas dependências

- Rodar os comandos

```
shedskin vri.py
make
./vri
```

### Utils:

```
python -m cProfile -o prof.dat vri.py
python -m pstats prof.dat
sort time
stats
```
Tempo gasto em cada função com tol = 0.01 recursivo (execução em Python):

```
         315522487 function calls (283463011 primitive calls) in 122.275 seconds

   Ordered by: internal time

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
 81165210   58.775    0.000   81.665    0.000 vri.py:60(opacidade)
16233042/381264   26.399    0.000  118.019    0.000 vri.py:22(simpson)
162330420   22.890    0.000   22.890    0.000 vri.py:19(acesso)
16233042/25344    8.053    0.000  118.230    0.005 vri.py:48(simpsonAdaptativo)
        1    2.643    2.643  122.275  122.275 vri.py:1(<module>)
  1906320    1.145    0.000  117.288    0.000 vri.py:73(funcaoRenderizacaoVolumetrica)
 16233042    0.787    0.000    0.787    0.000 {abs}
  6488065    0.740    0.000    0.740    0.000 {method 'read' of 'file' objects}
  6500736    0.337    0.000    0.337    0.000 {method 'append' of 'list' objects}
  6488064    0.311    0.000    0.311    0.000 {ord}
  1906320    0.181    0.000    0.181    0.000 {math.exp}
    25344    0.008    0.000  118.238    0.005 vri.py:77(integralRenderizacaoVolumetrica)
        1    0.003    0.003    0.005    0.005 vri.py:7(pgmwrite)
    12774    0.001    0.000    0.001    0.000 {method 'write' of 'file' objects}
        1    0.001    0.001    0.001    0.001 {method 'sort' of 'list' objects}
        2    0.000    0.000    0.000    0.000 {open}
        2    0.000    0.000    0.000    0.000 {method 'close' of 'file' objects}
      100    0.000    0.000    0.000    0.000 {range}
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}
```

A execução pelo shedskin leva pouco mais de 1 segundo com os mesmos valores de tolerância.

### TODO:

- Shear Warp
