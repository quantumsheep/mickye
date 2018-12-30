#include "terminal.h"

void
call_terminal()
{
    create_window("Terminal", 800, 600);
    error_modal("Ceci est un message d'erreur");
}