// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino


#ifndef AUXILIAR_H
#define AUXILIAR_H

// Imprime por pantalla el "Error [N de Error]: [Descripción del error]"
// en rojo porque mola el color rojo
void Aux_general_Imprimir_Error();

// Devuelve el valor numérico de las diferentes "flags" de apertura
int Aux_general_get_flag(const char *mode);

#endif //AUXILIAR_H
