#include "gui/gui.h"
#include "handlers/tcp.h"

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
    builder = open_builder();
    if(builder == NULL) return 1;

    /**
     * Link widgets to signal handlers
     */
    add_handler(builder, "window", "destroy", gtk_main_quit);
    add_handler(builder, "terminal_window", "destroy", gtk_main_quit);
    add_handler(builder, "start", "clicked", start_server);
    add_handler(builder, "stop", "clicked", gtk_main_quit);
    add_handler(builder, "terminal", "clicked", call_terminal);
    add_handler(builder, "quit", "clicked", gtk_main_quit);

    gtk_main();

    return 0;
}
