#pragma once

#include <stdio.h>

typedef struct person {
  const char *name;
  int age;
} Person;

int person_age_by(Person *person, int years);
void person_greet(FILE *stream, Person *person);
