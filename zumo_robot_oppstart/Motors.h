class Motors {
    public:
    Belt left_belt;
    Belt right_belt;

    Motors() = default;
};

class Belt {
    public:
    bool encoder_1_error;
    bool encoder_2_error;

    bool check_if_encoder_error();
    bool get_counts();
};