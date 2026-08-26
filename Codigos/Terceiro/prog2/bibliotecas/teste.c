#include <glib.h>
int main() {
    GList* frutas = NULL;

    frutas = g_list_append(frutas, "Maçã");
    frutas = g_list_append(frutas, "Banana");
    frutas = g_list_remove(frutas, "Maçã");

    g_list_free(frutas);

    return 0;
}
