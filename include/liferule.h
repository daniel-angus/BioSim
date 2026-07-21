#ifndef RULE_H
#define RULE_H

#include <stdbool.h>

typedef struct {
    bool birth[9];
    bool survive[9];
} LifeRule;

LifeRule rule_conway(void);

int rule_parse(const char *notation, LifeRule *rule);

#endif