#include <string.h>
#include "GildedRose.h"
#include <stdio.h>

// Função auxiliar para verificar o nome do item de forma mais legível
int is_item(Item* item, const char* name) {
    return strcmp(item->name, name) == 0;
}

// Funções de atualização de qualidade separadas por tipo de item

void update_normal_item(Item* item) {
    if (item->quality > 0) {
        item->quality = item->quality - 1;
    }
    item->sellIn = item->sellIn - 1;
    if (item->sellIn < 0 && item->quality > 0) {
        item->quality = item->quality - 1;
    }
}

void update_aged_brie(Item* item) {
    if (item->quality < 50) {
        item->quality = item->quality + 1;
    }
    item->sellIn = item->sellIn - 1;
    if (item->sellIn < 0 && item->quality < 50) {
        item->quality = item->quality + 1;
    }
}

void update_sulfuras(Item* item) {
    // "Sulfuras" nunca muda, então a função está vazia.
    // A qualidade é lendária (80) e nunca se altera.
    // O sellIn também não se altera.
}

void update_backstage_pass(Item* item) {
    if (item->quality < 50) {
        item->quality = item->quality + 1;
        if (item->sellIn < 11 && item->quality < 50) {
            item->quality = item->quality + 1;
        }
        if (item->sellIn < 6 && item->quality < 50) {
            item->quality = item->quality + 1;
        }
    }

    item->sellIn = item->sellIn - 1;

    if (item->sellIn < 0) {
        item->quality = 0;
    }
}

// Nova funcionalidade implementada
void update_conjured_item(Item* item) {
    // Degrada duas vezes mais rápido que um item normal
    if (item->quality > 0) {
        item->quality = item->quality - 2;
    }
    item->sellIn = item->sellIn - 1;
    if (item->sellIn < 0 && item->quality > 0) {
        item->quality = item->quality - 2;
    }

    // Garante que a qualidade não fique negativa
    if (item->quality < 0) {
        item->quality = 0;
    }
}


void update_quality(Item items[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        // Usamos uma estrutura de dispatch para chamar a lógica correta
        if (is_item(&items[i], "Aged Brie")) {
            update_aged_brie(&items[i]);
        } else if (is_item(&items[i], "Backstage passes to a TAFKAL80ETC concert")) {
            update_backstage_pass(&items[i]);
        } else if (is_item(&items[i], "Sulfuras, Hand of Ragnaros")) {
            update_sulfuras(&items[i]);
        } else if (is_item(&items[i], "Conjured Mana Cake")) {
            update_conjured_item(&items[i]);
        } else {
            // Item padrão
            update_normal_item(&items[i]);
        }
    }
}

// As funções init_item e print_item permanecem as mesmas
Item*
init_item(Item* item, const char *name, int sellIn, int quality)
{
    item->sellIn = sellIn;
    item->quality = quality;
    item->name = strdup(name);

    return item;
}

extern char* print_item(char* buffer, Item* item)
{
    sprintf(buffer, "%s, %d, %d", item->name, item->sellIn, item->quality);
}
