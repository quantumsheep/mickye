#include <gtk/gtk.h>

void
client_add(GtkListStore *store, char *ip_str, char *status);

void
client_connect(GtkWidget *connect_button, GtkBuilder *builder);