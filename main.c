#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_MATERIAS 100
#define MAX_ESTUDIANTES 30
#define MAX_PROFESORES 50
#define MAX_CURSOS 50
#define MAX_CODIGO 20
#define MAX_USUARIO 50
#define MAX_NOMBRE 100

// Estructuras
typedef struct {
    char nombre[MAX_NOMBRE];
    char codigo[MAX_CODIGO];
    int estado; // 1 Activo, 0 Inactivo
} Materia;

typedef struct {
    char matricula[MAX_CODIGO];
    char nombres[MAX_NOMBRE];
    char apellidos[MAX_NOMBRE];
    char usuario[MAX_USUARIO];
    char clave[MAX_USUARIO];
    int estado; // 1 Activo, 0 Inactivo
} Estudiante;

typedef struct {
    char cc[MAX_CODIGO]; // C.C. (cédula de ciudadanía)
    char nombres[MAX_NOMBRE];
    char apellidos[MAX_NOMBRE];
    char usuario[MAX_USUARIO];
    char clave[MAX_USUARIO];
    int estado; // 1 Activo, 0 Inactivo
    char materias[MAX_MATERIAS][MAX_CODIGO]; // Materias que puede dictar
} Profesor;

typedef struct {
    char codigo[MAX_CODIGO];
    Materia materia;
    Profesor profesor;
    struct tm fecha_inicio;
    struct tm fecha_fin;
    Estudiante estudiantes[MAX_ESTUDIANTES];
    int num_estudiantes;
} Curso;

// Variables globales
Materia materias[MAX_MATERIAS];
Estudiante estudiantes[MAX_ESTUDIANTES];
Profesor profesores[MAX_PROFESORES];
Curso cursos[MAX_CURSOS];

int num_materias = 0;
int num_estudiantes = 0;
int num_profesores = 0;
int num_cursos = 0;

// Funciones auxiliares
int verificarMateriaExistente(char *codigo) {
    for (int i = 0; i < num_materias; i++) {
        if (strcmp(materias[i].codigo, codigo) == 0) {
            return 1; // Materia ya existe
        }
    }
    return 0;
}

int verificarEstudianteExistente(char *matricula, char *usuario) {
    for (int i = 0; i < num_estudiantes; i++) {
        if (strcmp(estudiantes[i].matricula, matricula) == 0 || strcmp(estudiantes[i].usuario, usuario) == 0) {
            return 1; // Estudiante ya existe
        }
    }
    return 0;
}

int verificarProfesorExistente(char *cc, char *usuario) {
    for (int i = 0; i < num_profesores; i++) {
        if (strcmp(profesores[i].cc, cc) == 0 || strcmp(profesores[i].usuario, usuario) == 0) {
            return 1; // Profesor ya existe
        }
    }
    return 0;
}

int verificarCursoExistente(char *codigo) {
    for (int i = 0; i < num_cursos; i++) {
        if (strcmp(cursos[i].codigo, codigo) == 0) {
            return 1; // Curso ya existe
        }
    }
    return 0;
}

int verificarEstudianteEnCurso(char *matricula) {
    for (int i = 0; i < num_cursos; i++) {
        for (int j = 0; j < cursos[i].num_estudiantes; j++) {
            if (strcmp(cursos[i].estudiantes[j].matricula, matricula) == 0) {
                return 1; // Estudiante está en curso
            }
        }
    }
    return 0;
}

int verificarProfesorEnCurso(char *cc) {
    for (int i = 0; i < num_cursos; i++) {
        if (strcmp(cursos[i].profesor.cc, cc) == 0) {
            return 1; // Profesor tiene un curso en proceso
        }
    }
    return 0;
}

// Funciones de menú
void mostrarMenu() {
    printf("\nMenú:\n");
    printf("a. Materia\n");
    printf("b. Estudiante\n");
    printf("c. Profesor\n");
    printf("d. Curso\n");
    printf("e. Salir\n");
    printf("Seleccione una opción: ");
}

// Funciones para Materias
void crearMateria() {
    if (num_materias >= MAX_MATERIAS) {
        printf("No se pueden agregar más materias.\n");
        return;
    }

    Materia m;
    printf("\nCrear Materia\n");
    printf("Ingrese el nombre de la materia: ");
    getchar(); // Limpiar buffer
    fgets(m.nombre, MAX_NOMBRE, stdin);
    m.nombre[strcspn(m.nombre, "\n")] = '\0'; // Eliminar salto de línea

    printf("Ingrese el código de la materia: ");
    fgets(m.codigo, MAX_CODIGO, stdin);
    m.codigo[strcspn(m.codigo, "\n")] = '\0'; // Eliminar salto de línea

    if (verificarMateriaExistente(m.codigo)) {
        printf("La materia con ese código ya existe.\n");
        return;
    }

    printf("Ingrese el estado (1 para Activo, 0 para Inactivo): ");
    scanf("%d", &m.estado);

    if (m.estado != 1 && m.estado != 0) {
        printf("Estado inválido.\n");
        return;
    }

    materias[num_materias++] = m;
    printf("Materia creada con éxito.\n");
}

void editarMateria() {
    char codigo[MAX_CODIGO];
    printf("\nEditar Materia\n");
    printf("Ingrese el código de la materia a editar: ");
    getchar(); // Limpiar buffer
    fgets(codigo, MAX_CODIGO, stdin);
    codigo[strcspn(codigo, "\n")] = '\0'; // Eliminar salto de línea

    int idx = -1;
    for (int i = 0; i < num_materias; i++) {
        if (strcmp(materias[i].codigo, codigo) == 0) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("Materia no encontrada.\n");
        return;
    }

    if (verificarCursoExistente(codigo)) {
        printf("No se puede inactivar la materia porque tiene un curso en proceso.\n");
        return;
    }

    printf("Ingrese el nuevo estado (1 para Activo, 0 para Inactivo): ");
    scanf("%d", &materias[idx].estado);

    if (materias[idx].estado != 1 && materias[idx].estado != 0) {
        printf("Estado inválido.\n");
        return;
    }

    printf("Materia editada con éxito.\n");
}

// Funciones para Estudiantes
void crearEstudiante() {
    if (num_estudiantes >= MAX_ESTUDIANTES) {
        printf("No se pueden agregar más estudiantes.\n");
        return;
    }

    Estudiante e;
    printf("\nCrear Estudiante\n");
    printf("Ingrese los nombres: ");
    getchar(); // Limpiar buffer
    fgets(e.nombres, MAX_NOMBRE, stdin);
    e.nombres[strcspn(e.nombres, "\n")] = '\0'; // Eliminar salto de línea

    printf("Ingrese los apellidos: ");
    fgets(e.apellidos, MAX_NOMBRE, stdin);
    e.apellidos[strcspn(e.apellidos, "\n")] = '\0'; // Eliminar salto de línea

    printf("Ingrese la matrícula: ");
    fgets(e.matricula, MAX_CODIGO, stdin);
    e.matricula[strcspn(e.matricula, "\n")] = '\0'; // Eliminar salto de línea

    if (verificarEstudianteExistente(e.matricula, "")) {
        printf("La matrícula ya existe.\n");
        return;
    }

    printf("Ingrese el usuario: ");
    fgets(e.usuario, MAX_USUARIO, stdin);
    e.usuario[strcspn(e.usuario, "\n")] = '\0'; // Eliminar salto de línea

    if (verificarEstudianteExistente("", e.usuario)) {
        printf("El usuario ya existe.\n");
        return;
    }

    printf("Ingrese la clave: ");
    fgets(e.clave, MAX_USUARIO, stdin);
    e.clave[strcspn(e.clave, "\n")] = '\0'; // Eliminar salto de línea

    printf("Ingrese el estado (1 para Activo, 0 para Inactivo): ");
    scanf("%d", &e.estado);

    if (e.estado != 1 && e.estado != 0) {
        printf("Estado inválido.\n");
        return;
    }

    estudiantes[num_estudiantes++] = e;
    printf("Estudiante creado con éxito.\n");
}

void editarEstudiante() {
    char matricula[MAX_CODIGO];
    printf("\nEditar Estudiante\n");
    printf("Ingrese la matrícula del estudiante a editar: ");
    getchar(); // Limpiar buffer
    fgets(matricula, MAX_CODIGO, stdin);
    matricula[strcspn(matricula, "\n")] = '\0'; // Eliminar salto de línea

    int idx = -1;
    for (int i = 0; i < num_estudiantes; i++) {
        if (strcmp(estudiantes[i].matricula, matricula) == 0) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("Estudiante no encontrado.\n");
        return;
    }

    if (verificarEstudianteEnCurso(matricula)) {
        printf("No se puede inactivar al estudiante porque tiene un curso en proceso.\n");
        return;
    }

    printf("Ingrese la nueva clave: ");
    fgets(estudiantes[idx].clave, MAX_USUARIO, stdin);
    estudiantes[idx].clave[strcspn(estudiantes[idx].clave, "\n")] = '\0'; // Eliminar salto de línea

    printf("Ingrese el nuevo estado (1 para Activo, 0 para Inactivo): ");
    scanf("%d", &estudiantes[idx].estado);

    if (estudiantes[idx].estado != 1 && estudiantes[idx].estado != 0) {
        printf("Estado inválido.\n");
        return;
    }

    printf("Estudiante editado con éxito.\n");
}

// Funciones para Profesores
void crearProfesor() {
    if (num_profesores >= MAX_PROFESORES) {
        printf("No se pueden agregar más profesores.\n");
        return;
    }

    Profesor p;
    printf("\nCrear Profesor\n");
    printf("Ingrese los nombres: ");
    getchar(); // Limpiar buffer de la entrada anterior
    fgets(p.nombres, MAX_NOMBRE, stdin);
    p.nombres[strcspn(p.nombres, "\n")] = '\0'; // Eliminar salto de línea

    printf("Ingrese los apellidos: ");
    fgets(p.apellidos, MAX_NOMBRE, stdin);
    p.apellidos[strcspn(p.apellidos, "\n")] = '\0'; // Eliminar salto de línea

    printf("Ingrese la C.C.: ");
    fgets(p.cc, MAX_CODIGO, stdin);
    p.cc[strcspn(p.cc, "\n")] = '\0'; // Eliminar salto de línea

    if (verificarProfesorExistente(p.cc, "")) {
        printf("El profesor con esa C.C. ya existe.\n");
        return;
    }

    printf("Ingrese el usuario: ");
    fgets(p.usuario, MAX_USUARIO, stdin);
    p.usuario[strcspn(p.usuario, "\n")] = '\0'; // Eliminar salto de línea

    if (verificarProfesorExistente("", p.usuario)) {
        printf("El usuario ya existe.\n");
        return;
    }

    printf("Ingrese la clave: ");
    fgets(p.clave, MAX_USUARIO, stdin);
    p.clave[strcspn(p.clave, "\n")] = '\0'; // Eliminar salto de línea

    printf("Ingrese el estado (1 para Activo, 0 para Inactivo): ");
    scanf("%d", &p.estado);

    if (p.estado != 1 && p.estado != 0) {
        printf("Estado inválido.\n");
        return;
    }

    // Ingresar materias que puede dictar
    int j = 0;
    while (1) {
        printf("Ingrese la materia %d (ingrese '0' para terminar): ", j + 1);
        getchar(); // Limpiar el salto de línea dejado por el scanf previo
        fgets(p.materias[j], MAX_CODIGO, stdin);

        // Eliminar el salto de línea al final de la entrada
        p.materias[j][strcspn(p.materias[j], "\n")] = '\0'; 

        // Si se ingresa '0', se sale del ciclo
        if (strcmp(p.materias[j], "0") == 0) {
            break;
        }

        j++;  // Aumentar el índice de materias

        if (j >= MAX_MATERIAS) {  // Limitar el número de materias
            printf("Máximo de materias alcanzado.\n");
            break;
        }
    }

    profesores[num_profesores++] = p;
    printf("Profesor creado con éxito.\n");
}


void editarProfesor() {
    char cc[MAX_CODIGO];
    printf("\nEditar Profesor\n");
    printf("Ingrese la C.C. del profesor a editar: ");
    getchar(); // Limpiar buffer
    fgets(cc, MAX_CODIGO, stdin);
    cc[strcspn(cc, "\n")] = '\0'; // Eliminar salto de línea

    int idx = -1;
    for (int i = 0; i < num_profesores; i++) {
        if (strcmp(profesores[i].cc, cc) == 0) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("Profesor no encontrado.\n");
        return;
    }

    if (verificarProfesorEnCurso(cc)) {
        printf("No se puede inactivar al profesor porque tiene un curso en proceso.\n");
        return;
    }

    printf("Ingrese la nueva clave: ");
    fgets(profesores[idx].clave, MAX_USUARIO, stdin);
    profesores[idx].clave[strcspn(profesores[idx].clave, "\n")] = '\0'; // Eliminar salto de línea

    printf("Ingrese el nuevo estado (1 para Activo, 0 para Inactivo): ");
    scanf("%d", &profesores[idx].estado);

    if (profesores[idx].estado != 1 && profesores[idx].estado != 0) {
        printf("Estado inválido.\n");
        return;
    }

    printf("Profesor editado con éxito.\n");
}

// Funciones para Cursos
void crearCurso() {
    if (num_cursos >= MAX_CURSOS) {
        printf("No se pueden agregar más cursos.\n");
        return;
    }

    Curso c;
    printf("\nCrear Curso\n");
    printf("Ingrese el código del curso: ");
    getchar(); // Limpiar buffer
    fgets(c.codigo, MAX_CODIGO, stdin);
    c.codigo[strcspn(c.codigo, "\n")] = '\0'; // Eliminar salto de línea

    if (verificarCursoExistente(c.codigo)) {
        printf("El curso con ese código ya existe.\n");
        return;
    }

    printf("Ingrese la materia del curso: ");
    fgets(c.materia.codigo, MAX_CODIGO, stdin);
    c.materia.codigo[strcspn(c.materia.codigo, "\n")] = '\0'; // Eliminar salto de línea

    // Buscar la materia
    int idx_materia = -1;
    for (int i = 0; i < num_materias; i++) {
        if (strcmp(materias[i].codigo, c.materia.codigo) == 0) {
            idx_materia = i;
            break;
        }
    }
    if (idx_materia == -1) {
        printf("Materia no encontrada.\n");
        return;
    }
    c.materia = materias[idx_materia];

    printf("Ingrese el C.C. del profesor: ");
    fgets(c.profesor.cc, MAX_CODIGO, stdin);
    c.profesor.cc[strcspn(c.profesor.cc, "\n")] = '\0'; // Eliminar salto de línea

    // Buscar el profesor
    int idx_profesor = -1;
    for (int i = 0; i < num_profesores; i++) {
        if (strcmp(profesores[i].cc, c.profesor.cc) == 0) {
            idx_profesor = i;
            break;
        }
    }
    if (idx_profesor == -1) {
        printf("Profesor no encontrado.\n");
        return;
    }
    c.profesor = profesores[idx_profesor];

    printf("Ingrese la fecha de inicio (formato: YYYY-MM-DD): ");
    scanf("%d-%d-%d", &c.fecha_inicio.tm_year, &c.fecha_inicio.tm_mon, &c.fecha_inicio.tm_mday);
    c.fecha_inicio.tm_year -= 1900; // Año desde 1900
    c.fecha_inicio.tm_mon -= 1; // Mes desde 0

    printf("Ingrese la fecha de fin (formato: YYYY-MM-DD): ");
    scanf("%d-%d-%d", &c.fecha_fin.tm_year, &c.fecha_fin.tm_mon, &c.fecha_fin.tm_mday);
    c.fecha_fin.tm_year -= 1900; // Año desde 1900
    c.fecha_fin.tm_mon -= 1; // Mes desde 0

    // Validar fechas
    if (difftime(mktime(&c.fecha_inicio), mktime(&c.fecha_fin)) > 0) {
        printf("La fecha de inicio no puede ser mayor que la fecha de fin.\n");
        return;
    }

    printf("Ingrese los estudiantes (máximo 30). Ingrese 'fin' para terminar.\n");
    int i; // Declarar la variable 'i' aquí
    for (i = 0; i < MAX_ESTUDIANTES; i++) {
        printf("Estudiante %d: ", i + 1);
        fgets(c.estudiantes[i].matricula, MAX_CODIGO, stdin);
        c.estudiantes[i].matricula[strcspn(c.estudiantes[i].matricula, "\n")] = '\0';
        if (strcmp(c.estudiantes[i].matricula, "fin") == 0) {
            break;
        }
    }
    c.num_estudiantes = i; // Ahora la variable 'i' está correctamente declarada

    cursos[num_cursos++] = c;
    printf("Curso creado con éxito.\n");
}

void editarCurso() {
    char codigo[MAX_CODIGO];
    printf("\nEditar Curso\n");
    printf("Ingrese el código del curso a editar: ");
    getchar(); // Limpiar buffer
    fgets(codigo, MAX_CODIGO, stdin);
    codigo[strcspn(codigo, "\n")] = '\0'; // Eliminar salto de línea

    int idx = -1;
    for (int i = 0; i < num_cursos; i++) {
        if (strcmp(cursos[i].codigo, codigo) == 0) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("Curso no encontrado.\n");
        return;
    }

    // Verificar si la fecha de inicio ya pasó
    struct tm now;
    time_t t = time(NULL);
    now = *localtime(&t);
    if (difftime(mktime(&now), mktime(&cursos[idx].fecha_inicio)) >= 0) {
        printf("El curso ya ha comenzado, no puede editarse.\n");
        return;
    }

    printf("Ingrese el nuevo código del curso: ");
    fgets(cursos[idx].codigo, MAX_CODIGO, stdin);
    cursos[idx].codigo[strcspn(cursos[idx].codigo, "\n")] = '\0'; // Eliminar salto de línea

    printf("Ingrese la nueva materia del curso: ");
    fgets(cursos[idx].materia.codigo, MAX_CODIGO, stdin);
    cursos[idx].materia.codigo[strcspn(cursos[idx].materia.codigo, "\n")] = '\0'; // Eliminar salto de línea

    // Buscar la nueva materia
    int idx_materia = -1;
    for (int i = 0; i < num_materias; i++) {
        if (strcmp(materias[i].codigo, cursos[idx].materia.codigo) == 0) {
            idx_materia = i;
            break;
        }
    }
    if (idx_materia == -1) {
        printf("Materia no encontrada.\n");
        return;
    }
    cursos[idx].materia = materias[idx_materia];

    printf("Ingrese el C.C. del profesor: ");
    fgets(cursos[idx].profesor.cc, MAX_CODIGO, stdin);
    cursos[idx].profesor.cc[strcspn(cursos[idx].profesor.cc, "\n")] = '\0'; // Eliminar salto de línea

    // Buscar el nuevo profesor
    int idx_profesor = -1;
    for (int i = 0; i < num_profesores; i++) {
        if (strcmp(profesores[i].cc, cursos[idx].profesor.cc) == 0) {
            idx_profesor = i;
            break;
        }
    }
    if (idx_profesor == -1) {
        printf("Profesor no encontrado.\n");
        return;
    }
    cursos[idx].profesor = profesores[idx_profesor];

    printf("Ingrese la nueva fecha de inicio (formato: YYYY-MM-DD): ");
    scanf("%d-%d-%d", &cursos[idx].fecha_inicio.tm_year, &cursos[idx].fecha_inicio.tm_mon, &cursos[idx].fecha_inicio.tm_mday);
    cursos[idx].fecha_inicio.tm_year -= 1900; // Año desde 1900
    cursos[idx].fecha_inicio.tm_mon -= 1; // Mes desde 0

    printf("Ingrese la nueva fecha de fin (formato: YYYY-MM-DD): ");
    scanf("%d-%d-%d", &cursos[idx].fecha_fin.tm_year, &cursos[idx].fecha_fin.tm_mon, &cursos[idx].fecha_fin.tm_mday);
    cursos[idx].fecha_fin.tm_year -= 1900; // Año desde 1900
    cursos[idx].fecha_fin.tm_mon -= 1; // Mes desde 0

    // Validar fechas
    if (difftime(mktime(&cursos[idx].fecha_inicio), mktime(&cursos[idx].fecha_fin)) > 0) {
        printf("La fecha de inicio no puede ser mayor que la fecha de fin.\n");
        return;
    }

    printf("Curso editado con éxito.\n");
}

int main() {
    char opcion;

    while (1) {
        mostrarMenu();
        scanf(" %c", &opcion);

        switch (opcion) {
            case 'a':
                printf("\nOpciones de Materia:\n");
                printf("1. Crear Materia\n");
                printf("2. Editar Materia\n");
                printf("Seleccione una opción: ");
                int opMateria;
                scanf("%d", &opMateria);
                if (opMateria == 1) {
                    crearMateria();
                } else if (opMateria == 2) {
                    editarMateria();
                }
                break;

            case 'b':
                printf("\nOpciones de Estudiante:\n");
                printf("1. Crear Estudiante\n");
                printf("2. Editar Estudiante\n");
                printf("Seleccione una opción: ");
                int opEstudiante;
                scanf("%d", &opEstudiante);
                if (opEstudiante == 1) {
                    crearEstudiante();
                } else if (opEstudiante == 2) {
                    editarEstudiante();
                }
                break;

            case 'c':
                printf("\nOpciones de Profesor:\n");
                printf("1. Crear Profesor\n");
                printf("2. Editar Profesor\n");
                printf("Seleccione una opción: ");
                int opProfesor;
                scanf("%d", &opProfesor);
                if (opProfesor == 1) {
                    crearProfesor();
                } else if (opProfesor == 2) {
                    editarProfesor();
                }
                break;

            case 'd':
                printf("\nOpciones de Curso:\n");
                printf("1. Crear Curso\n");
                printf("2. Editar Curso\n");
                printf("Seleccione una opción: ");
                int opCurso;
                scanf("%d", &opCurso);
                if (opCurso == 1) {
                    crearCurso();
                } else if (opCurso == 2) {
                    editarCurso();
                }
                break;

            case 'e':
                printf("Saliendo del programa...\n");
                return 0;

            default:
                printf("Opción inválida. Intente nuevamente.\n");
        }
    }

    return 0;
}
