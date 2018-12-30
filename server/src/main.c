#include "gui/gui.h"
#include "handlers/tcp.h"

void
list_clients()
{

}

int
main (int argc, char **argv)
{
    GtkBuilder* builder;

    gtk_init(&argc, &argv);

    /**
     * Construct a GtkBuilder instance and load our UI description
     * 
     * The builder.ui file can be edited before launching the software
     * in order to customize the interface
     */
    builder = gui_open_builder();
    if(builder == NULL) return 1;

    /**
     * Link widgets to signal handlers
     */
    gui_add_handler(builder, "window", "destroy", gtk_main_quit);
    gui_add_handler(builder, "start", "clicked", start_server);
    gui_add_handler(builder, "stop", "clicked", gtk_main_quit);
    gui_add_handler(builder, "terminal", "clicked", call_terminal);
    gui_add_handler(builder, "quit", "clicked", gtk_main_quit);

    list_clients();

    gtk_main();

    return 0;
}
