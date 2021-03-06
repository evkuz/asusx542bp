#ifndef EVKUZ_H
#define EVKUZ_H

/*
 * Выражение X = W*I Используется для вычисления значения сигнала,
 * проходящего от одного слоя к следующему.
 * W - вес сигнала (весовой коэффициент)
 * I - Значение входного сигнала

  w11=0,9  w12=0,2
  W21=0,3  w22=0,8

        (0,9)
  I =   (0,1)
        (0,8)


                    (0,9  0,3  0,4)
  Wвходной_скрытый =(0,2  0,8  0,2)
                    (0,1  0,5  0,6)

  Xскрытый = I*Wвходноый_скрытый

            (1.16)
  Xскрытый =(0.42)
            (0.62)

                     (0,3  0,7  0,5)
  Wскрытый_выходной =(0,6  0,5  0,2)
                     (0,8  0,1  0,9)



 Чтобы получиить отклик слоя нужно применить ф-цию активации

 Oскрытый = СИГМОИДА(Xскрытый)

            (0.761)
 Oскрытый = (0.603)
            (0.650)


*/
#endif // EVKUZ_H
