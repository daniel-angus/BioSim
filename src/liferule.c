#include <string.h>
#include "liferule.h"

LifeRule rule_conway(void) {
    LifeRule rule = {0};

    rule.birth[3] = true;
    rule.survive[2] = true;
    rule.survive[3] = true;

    return rule;
}

int rule_parse(const char *notation, LifeRule *rule) {
    if (notation == NULL || rule == NULL) {
        return 0;
    }

    memset(rule, 0, sizeof *rule);

    size_t i = 0;

    if (notation[i] != 'B') {
        return 0;
    }

    i++;

    while (notation[i] != '/') {
        if (notation[i] == '\0') {
            return 0;
        }

        if (notation[i] < '0' || notation[i] > '8') {
            return 0;
        }

        int neighbours = notation[i] - '0';
        rule->birth[neighbours] = true;

        i++;
    }

    i++;

    if (notation[i] != 'S') {
        return 0;
    }

    i++;

    while (notation[i] != '\0') {
        if (notation[i] < '0' || notation[i] > '8') {
            return 0;
        }

        int neighbours = notation[i] - '0';
        rule->survive[neighbours] = true;

        i++;
    }

    return 1;
}