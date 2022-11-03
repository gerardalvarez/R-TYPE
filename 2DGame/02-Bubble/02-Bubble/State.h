class State {
public:
    enum class State_enum { MENU, GAME, CREDITS, INFO, WIN };

    State();

    ~State();

    void init();

    void changeState();

    void goCREDITS();

    void goMENU();

    void goGAME();

    void goINFO();

    void goWIN();

    State_enum getState();


private:
    State_enum state;

};



