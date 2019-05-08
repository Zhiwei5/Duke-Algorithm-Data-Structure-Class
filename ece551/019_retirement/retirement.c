#include <stdio.h>
#include <stdlib.h>

typedef struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
} retire_info_t;

double calculate_balence(double balence, double contribution, double rate_of_return) {
  return balence + balence * rate_of_return + contribution;
}

void retirement(int startAge, double initial, retire_info_t working, retire_info_t retired) {
  int work_month = working.months;
  int retire_month = retired.months;
  double balence = initial;
  int i;
  int age_month = startAge;
  for (i = 0; i < work_month; i++) {
    int age = age_month / 12;
    int month = age_month % 12;
    printf("Age %3d month %2d you have $%.2lf\n", age, month, balence);
    balence = calculate_balence(balence, working.contribution, working.rate_of_return);
    age_month++;
  }
  for (i = 0; i < retire_month; i++) {
    int age = age_month / 12;
    int month = age_month % 12;
    double interest_rate = retired.rate_of_return;
    printf("Age %3d month %2d you have $%.2lf\n", age, month, balence);
    balence = calculate_balence(balence, retired.contribution, interest_rate);
    age_month++;
  }
}

int main() {
  int startAge = 327;
  double initial = 21345;
  retire_info_t working = {489, 1000, 4.5 / 1200};
  retire_info_t retired = {384, -4000, 0.01 / 12};
  retirement(startAge, initial, working, retired);
  return 1;
}
