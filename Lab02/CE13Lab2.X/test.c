double Round(double operand);

int main(void)
{
    double operand = 10.9;
    int result = Round(operand);
    printf("Result of round(%f): %d \n", operand, result);

}

double Round(double operand)
{
    //  Takes numbers and increments by 0.5 respective to sign
    double rounded = operand;
    if (operand > 0) {
        rounded += 0.5;
        printf("positive\n");
    } else {
        rounded -= 0.5;
        printf("negative\n");
    }
    // Returns double to be truncated after called
    return rounded;
}