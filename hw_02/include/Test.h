#ifndef LAB11_TEST_H_INCLUDED
#define LAB11_TEST_H_INCLUDED

#define DO_CHECK(EXPR) Test::check(EXPR, __func__, __FILE__, __LINE__);


class Test {
protected:
    static int failedNum; // количество тестов, которые сломались
    static int totalNum;  // общее количество тестов
    /** Проверяет условие (expr) на верность в конце теста.
        В одном тесте может быть не более одного `check`.
        Сообщает об результате пользователю, в случае неудачи подробно сообщает об источнике. */
    static void check(bool expr, const char *func, const char  *filename, size_t lineNum); 

public:
    /** Вызывается один раз в конце автотестов, выводит общую статистику по
        пройденным тестам на экран. Возвращает `true` если и только если
        все тесты успешно пройдены. */
    static bool showFinalResult();
    
    /** Запускает все тесты в конкретном наборе тестов */
    virtual void runAllTests() = 0;

    // Можно добавлять методы при необходимости 
};

#endif