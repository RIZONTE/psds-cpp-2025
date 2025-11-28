//Футы в дюймы
constexpr double operator""_ft_to_in(long double ft) {
    return ft * 12.0;
}

//Футы в сантиметры
constexpr double operator""_ft_to_cm(long double ft) {
    return ft * 30.48;
}

//Футы в метры
constexpr double operator""_ft_to_m(long double ft) {
    return ft * 0.3048;
}

//Дюймы в футы
constexpr double operator""_in_to_ft(long double in) {
    return in / 12.0;
}

//Дюймы в сантиметры
constexpr double operator""_in_to_cm(long double in) {
    return in * 2.54;
}

//Дюймы в метры
constexpr double operator""_in_to_m(long double in) {
    return in * 0.0254;
}

//Сантиметры в футы
constexpr double operator""_cm_to_ft(long double cm) {
    return cm / 30.48;
}

//Сантиметры в дюймы
constexpr double operator""_cm_to_in(long double cm) {
    return cm / 2.54;
}

//Сантиметры в метры
constexpr double operator""_cm_to_m(long double cm) {
    return cm * 0.01;
}

//Метры в футы
constexpr double operator""_m_to_ft(long double m) {
    return m / 0.3048;
}

//Метры в дюймы
constexpr double operator""_m_to_in(long double m) {
    return m / 0.0254;
}

//Метры в сантиметры
constexpr double operator""_m_to_cm(long double m) {
    return m * 100;
}