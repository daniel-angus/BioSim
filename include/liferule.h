#ifndef RULE_H
#define RULE_H

#include <stdbool.h>

typedef struct {
    bool birth[9];
    bool survive[9];
} LifeRule;

int rule_parse(const char *notation, LifeRule *rule);

#endif
