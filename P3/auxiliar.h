// Pablo Portas López           pablo.portas
// Pablo Míguez Mouiño          pablo.miguez.moino


#ifndef AUXILIAR_H
#define AUXILIAR_H

// Imprime por stderr un mensaje de error. Existen 4 variantes dependiendo la situación y los parámetros:
// 1 - Error Desconocido
// 2 - Error: [Descripción auxiliar |msg|]
// 3 - Error [N de Error]: [Descripción del error]
// 4 - Error [N de Error]: [Descripción auxiliar |msg|] - [Descripción del error]
// en rojo porque mola el color rojo
void Aux_general_Imprimir_Error(char *msg);

void Aux_general_handler(int sig);

#endif //AUXILIAR_H
