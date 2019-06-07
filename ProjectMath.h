#ifndef PROJECTMATH_H
#define PROJECTMATH_H

#include <tuple>

// Вся математика здесь сделана в ознакомительных целях.
// Для проектов ее нужно заменить на более точную и правильную

// Работает только в диапазоне (-2PI ; 2PI]
double DeltaAngle(double a, double b);

// Допуск необходимо смотреть внутри
bool IsDoubleEqual(double a, double b);

// Определяемая длина больше на 2 процента. В особых точках 3 процента.
// Можно заменить на более точный расчет
// Гинзбург Г. А., Салманова Т. Д. Тр. ЦНИИГАиК. М.: Недра. 1964. Вып. 160. 340 с.
double GetDistance(double B1, double L1, double B2, double L2);

// Конвертирует значение в градусы, минуты и секунды отдельно.
std::tuple<char, int, int, int> GradMinSec(double value);

#endif // PROJECTMATH_H
