#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MATERIAS 100
#define MAX_ESTUDIANTES 100
#define MAX_PROFESORES 100
#define MAX_CURSOS 100

// Estructuras de datos
typedef struct {
    char nombre[50];
    char codigo[20];
    int estado; // 1: Activo, 0: Inactivo
} Materia;

typedef struct {
    char nombres[50];
    char apellidos[50];
    char matricula[20];
    char usuario[20];
    char clave[20];
    int estado; // 1: Activo, 0: Inactivo
} Estudiante;

typedef struct {
    char nombres[50];
    char apellidos[50];
    char cc[20];
    char usuario[20];
    char clave[20];
    int estado; // 1: Activo, 0: Inactivo
    char materias[500]; // Listado de materias que puede dictar
} Profesor;

typedef struct {
    char codigo[20];
    char codigoMateria[20];
    char ccProfesor[20];
    char fechaInicio[20];
    char fechaFin[20];
    char matriculasEstudiantes[500]; // Listado de matrículas de estudiantes
} Curso;

// Arreglos globales para almacenar los datos
Materia materias[MAX_MATERIAS];
Estudiante estudiantes[MAX_ESTUDIANTES];
Profesor profesores[MAX_PROFESORES];
Curso cursos[MAX_CURSOS];

// Contadores de registros
int materiaCount = 0;
int estudianteCount = 0;
int profesorCount = 0;
int cursoCount = 0;

// Funciones de archivo
void leerMaterias();
void guardarMaterias();
void leerEstudiantes();
void guardarEstudiantes();
void leerProfesores();
void guardarProfesores();
void leerCursos();
void guardarCursos();

// Funciones de menú y opciones
void mostrarMenu();
void ejecutarOpcion(char opcion);
void crearMateria();
void editarMateria();
void crearEstudiante();
void editarEstudiante();
void crearProfesor();
void editarProfesor();
void crearCurso();
void editarCurso();

// Función principal
int main() {
    char opcion;
    
    // Cargar los datos iniciales
    leerMaterias();
    leerEstudiantes();
    leerProfesores();
    leerCursos();

    while (1) {
        mostrarMenu();
        printf("Seleccione una opción: ");
        scanf(" %c", &opcion);
        ejecutarOpcion(opcion);
    }

    // Guardar los datos al finalizar
    guardarMaterias();
    guardarEstudiantes();
    guardarProfesores();
    guardarCursos();
    printf("Datos guardados correctamente.\n");

    return 0;
}

// Mostrar el menú principal
void mostrarMenu() {
    printf("\n--- Menú de Opciones ---\n");
    printf("a. Materia\n");
    printf("b. Estudiante\n");
    printf("c. Profesor\n");
    printf("d. Curso\n");
    printf("e. Salir\n");
}

// Ejecutar la opción seleccionada
void ejecutarOpcion(char opcion) {
    switch (opcion) {
        case 'a':
            printf("a. Materia\n");
            printf("1. Crear\n");
            printf("2. Editar\n");
            char opcionMateria;
            scanf(" %c", &opcionMateria);
            if (opcionMateria == '1') crearMateria();
            else if (opcionMateria == '2') editarMateria();
            break;
        case 'b':
            printf("b. Estudiante\n");
            printf("1. Crear\n");
            printf("2. Editar\n");
            char opcionEstudiante;
            scanf(" %c", &opcionEstudiante);
            if (opcionEstudiante == '1') crearEstudiante();
            else if (opcionEstudiante == '2') editarEstudiante();
            break;
        case 'c':
            printf("c. Profesor\n");
            printf("1. Crear\n");
            printf("2. Editar\n");
            char opcionProfesor;
            scanf(" %c", &opcionProfesor);
            if (opcionProfesor == '1') crearProfesor();
            else if (opcionProfesor == '2') editarProfesor();
            break;
        case 'd':
            printf("d. Curso\n");
            printf("1. Crear\n");
            printf("2. Editar\n");
            char opcionCurso;
            scanf(" %c", &opcionCurso);
            if (opcionCurso == '1') crearCurso();
            else if (opcionCurso == '2') editarCurso();
            break;
        case 'e':
            printf("Saliendo...\n");
            exit(0);
        default:
            printf("Opción no válida.\n");
            break;
    }
}

// Crear Materia
void crearMateria() {
    Materia m;
    printf("Ingrese el nombre de la materia: ");
    scanf(" %[^\n]", m.nombre);
    printf("Ingrese el código de la materia: ");
    scanf(" %s", m.codigo);
    m.estado = 1; // Estado activo por defecto

    // Verificar que el código de la materia no exista
    for (int i = 0; i < materiaCount; i++) {
        if (strcmp(m.codigo, materias[i].codigo) == 0) {
            printf("El código de la materia ya existe.\n");
            return;
        }
    }

    materias[materiaCount++] = m;
    printf("Materia creada exitosamente.\n");
    guardarMaterias();  // Guardar los datos inmediatamente en el archivo
}

// Editar Materia
void editarMateria() {
    char codigo[20];
    printf("Ingrese el código de la materia a editar: ");
    scanf(" %s", codigo);

    for (int i = 0; i < materiaCount; i++) {
        if (strcmp(materias[i].codigo, codigo) == 0) {
            printf("Materia encontrada: %s\n", materias[i].nombre);
            printf("Cambiar estado (1: Activo, 0: Inactivo): ");
            int nuevoEstado;
            scanf("%d", &nuevoEstado);
            if (nuevoEstado != 1 && nuevoEstado != 0) {
                printf("Estado no válido.\n");
                return;
            }
            materias[i].estado = nuevoEstado;
            printf("Estado de la materia actualizado.\n");
            guardarMaterias();  // Guardar los datos inmediatamente en el archivo
            return;
        }
    }
    printf("Materia no encontrada.\n");
}

// Crear Estudiante
void crearEstudiante() {
    Estudiante e;
    printf("Ingrese los nombres del estudiante: ");
    scanf(" %[^\n]", e.nombres);
    printf("Ingrese los apellidos del estudiante: ");
    scanf(" %[^\n]", e.apellidos);
    printf("Ingrese la matrícula: ");
    scanf(" %s", e.matricula);
    printf("Ingrese el usuario: ");
    scanf(" %s", e.usuario);
    printf("Ingrese la clave: ");
    scanf(" %s", e.clave);
    e.estado = 1; // Estado activo por defecto

    // Verificar que la matrícula y el usuario sean únicos
    for (int i = 0; i < estudianteCount; i++) {
        if (strcmp(e.matricula, estudiantes[i].matricula) == 0 || strcmp(e.usuario, estudiantes[i].usuario) == 0) {
            printf("La matrícula o el usuario ya existe.\n");
            return;
        }
    }

    estudiantes[estudianteCount++] = e;
    printf("Estudiante creado exitosamente.\n");
    guardarEstudiantes();  // Guardar los datos inmediatamente en el archivo
}

// Editar Estudiante
void editarEstudiante() {
    char matricula[20];
    printf("Ingrese la matrícula del estudiante a editar: ");
    scanf(" %s", matricula);

    for (int i = 0; i < estudianteCount; i++) {
        if (strcmp(estudiantes[i].matricula, matricula) == 0) {
            printf("Estudiante encontrado: %s %s\n", estudiantes[i].nombres, estudiantes[i].apellidos);
            printf("Cambiar clave: ");
            scanf(" %s", estudiantes[i].clave);
            printf("Cambiar estado (1: Activo, 0: Inactivo): ");
            int nuevoEstado;
            scanf("%d", &nuevoEstado);
            estudiantes[i].estado = nuevoEstado;
            printf("Estudiante actualizado.\n");
            guardarEstudiantes();  // Guardar los datos inmediatamente en el archivo
            return;
        }
    }
    printf("Estudiante no encontrado.\n");
}

// Crear Profesor
void crearProfesor() {
    Profesor p;
    printf("Ingrese los nombres del profesor: ");
    scanf(" %[^\n]", p.nombres);
    printf("Ingrese los apellidos del profesor: ");
    scanf(" %[^\n]", p.apellidos);
    printf("Ingrese la cédula del profesor: ");
    scanf(" %s", p.cc);
    printf("Ingrese el usuario: ");
    scanf(" %s", p.usuario);
    printf("Ingrese la clave: ");
    scanf(" %s", p.clave);
    p.estado = 1; // Estado activo por defecto
    printf("Ingrese las materias que puede dictar (separadas por '/'): ");
    scanf(" %[^\n]", p.materias);

    // Verificar que la cédula y el usuario sean únicos
    for (int i = 0; i < profesorCount; i++) {
        if (strcmp(p.cc, profesores[i].cc) == 0 || strcmp(p.usuario, profesores[i].usuario) == 0) {
            printf("La cédula o el usuario ya existe.\n");
            return;
        }
    }

    profesores[profesorCount++] = p;
    printf("Profesor creado exitosamente.\n");
    guardarProfesores();  // Guardar los datos inmediatamente en el archivo
}

// Editar Profesor
void editarProfesor() {
    char cc[20];
    printf("Ingrese la cédula del profesor a editar: ");
    scanf(" %s", cc);

    for (int i = 0; i < profesorCount; i++) {
        if (strcmp(profesores[i].cc, cc) == 0) {
            printf("Profesor encontrado: %s %s\n", profesores[i].nombres, profesores[i].apellidos);
            printf("Cambiar clave: ");
            scanf(" %s", profesores[i].clave);
            printf("Cambiar estado (1: Activo, 0: Inactivo): ");
            int nuevoEstado;
            scanf("%d", &nuevoEstado);
            profesores[i].estado = nuevoEstado;
            printf("Profesor actualizado.\n");
            guardarProfesores();  // Guardar los datos inmediatamente en el archivo
            return;
        }
    }
    printf("Profesor no encontrado.\n");
}
int obtenerEstadoEstudiante(char *matricula) {
    for (int i = 0; i < estudianteCount; i++) {
        if (strcmp(estudiantes[i].matricula, matricula) == 0) {
            return estudiantes[i].estado; // Retorna 1 si activo, 0 si inactivo
        }
    }
    return -1; // No encontrado
}

// Función para crear un curso
void crearCurso() {
    Curso c;
    printf("Ingrese el código del curso: ");
    scanf(" %s", c.codigo);
    printf("Ingrese el código de la materia: ");
    scanf(" %s", c.codigoMateria);
    printf("Ingrese la cédula del profesor: ");
    scanf(" %s", c.ccProfesor);
    printf("Ingrese la fecha de inicio (dd/mm/yyyy): ");
    scanf(" %s", c.fechaInicio);
    printf("Ingrese la fecha de fin (dd/mm/yyyy): ");
    scanf(" %s", c.fechaFin);

    // Verificar que el curso no exista
    for (int i = 0; i < cursoCount; i++) {
        if (strcmp(c.codigo, cursos[i].codigo) == 0) {
            printf("El curso ya existe.\n");
            return;
        }
    }

    char buffer[1000];
    printf("Ingrese las matrículas de los estudiantes (separadas por '/'): ");
    scanf(" %[^\n]s", buffer);

    // Procesar las matrículas
    char matriculasEstudiantes[500] = ""; 
    char *token = strtok(buffer, "/");
    int estudiantesAgregados = 0;

    while (token != NULL) {
        int estadoEstudiante = obtenerEstadoEstudiante(token);

        if (estadoEstudiante == 1) { // Solo agregar si está activo
            if (estudiantesAgregados > 0) {
                strcat(matriculasEstudiantes, "/");
            }
            strcat(matriculasEstudiantes, token); // Concatenar matrícula
            estudiantesAgregados++;
        } else if (estadoEstudiante == 0) {
            printf("El estudiante con matrícula %s está inactivo y no será agregado.\n", token);
        } else {
            printf("El estudiante con matrícula %s no se encontró en el sistema.\n", token);
        }

        token = strtok(NULL, "/");
    }

    
    strcpy(c.matriculasEstudiantes, matriculasEstudiantes);

    /
    cursos[cursoCount++] = c;
    printf("Curso creado exitosamente con %d estudiantes activos.\n", estudiantesAgregados);

    guardarCursos();  // Guardar los datos inmediatamente en el archivo
}





// Editar Curso
void editarCurso() {
    char codigo[20];
    printf("Ingrese el código del curso a editar: ");
    scanf(" %s", codigo);

    for (int i = 0; i < cursoCount; i++) {
        if (strcmp(cursos[i].codigo, codigo) == 0) {
            printf("Curso encontrado: %s\n", cursos[i].codigo);
            printf("Cambiar fecha de inicio: ");
            scanf(" %s", cursos[i].fechaInicio);
            printf("Cambiar fecha de fin: ");
            scanf(" %s", cursos[i].fechaFin);
            printf("Curso actualizado.\n");
            guardarCursos();  // Guardar los datos inmediatamente en el archivo
            return;
        }
    }
    printf("Curso no encontrado.\n");
}

// Funciones para leer y guardar en archivos
void leerMaterias() {
    FILE *file = fopen("materias.txt", "r");
    if (file == NULL) return; // No hacer nada si el archivo no existe
    while (fscanf(file, "%[^/]/%[^/]/%d\n", materias[materiaCount].codigo, materias[materiaCount].nombre, &materias[materiaCount].estado) == 3) {
        materiaCount++;
    }
    fclose(file);
}

void guardarMaterias() {
    FILE *file = fopen("materias.txt", "w");
    if (file == NULL) return;
    for (int i = 0; i < materiaCount; i++) {
        fprintf(file, "%s/%s/%d\n", materias[i].codigo, materias[i].nombre, materias[i].estado);
    }
    fclose(file);
}

void leerEstudiantes() {
    FILE *file = fopen("estudiantes.txt", "r");
    if (file == NULL) return;
    while (fscanf(file, "%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%d\n", estudiantes[estudianteCount].matricula, estudiantes[estudianteCount].nombres, estudiantes[estudianteCount].apellidos, estudiantes[estudianteCount].usuario, estudiantes[estudianteCount].clave, &estudiantes[estudianteCount].estado) == 6) {
        estudianteCount++;
    }
    fclose(file);
}

void guardarEstudiantes() {
    FILE *file = fopen("estudiantes.txt", "w");
    if (file == NULL) return;
    for (int i = 0; i < estudianteCount; i++) {
        fprintf(file, "%s/%s/%s/%s/%s/%d\n", estudiantes[i].matricula, estudiantes[i].nombres, estudiantes[i].apellidos, estudiantes[i].usuario, estudiantes[i].clave, estudiantes[i].estado);
    }
    fclose(file);
}

void leerProfesores() {
    FILE *file = fopen("profesores.txt", "r");
    if (file == NULL) return;
    while (fscanf(file, "%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%d/%[^\n]\n", profesores[profesorCount].cc, profesores[profesorCount].nombres, profesores[profesorCount].apellidos, profesores[profesorCount].usuario, profesores[profesorCount].clave, &profesores[profesorCount].estado, profesores[profesorCount].materias) == 7) {
        profesorCount++;
    }
    fclose(file);
}

void guardarProfesores() {
    FILE *file = fopen("profesores.txt", "w");
    if (file == NULL) return;
    for (int i = 0; i < profesorCount; i++) {
        fprintf(file, "%s/%s/%s/%s/%s/%d/%s\n", profesores[i].cc, profesores[i].nombres, profesores[i].apellidos, profesores[i].usuario, profesores[i].clave, profesores[i].estado, profesores[i].materias);
    }
    fclose(file);
}



void leerCursos() {
    FILE *file = fopen("cursos.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%[^-]-%[^-]-%[^-]-%[^-]-%[^-]-%[^\n]",
                      cursos[num_cursos].codigo,
                      cursos[num_cursos].materia,
                      cursos[num_cursos].profesor,
                      cursos[num_cursos].fecha_inicio,
                      cursos[num_cursos].fecha_fin,
                      buffer) != EOF) {

        
            char *token = strtok(buffer, "/");
            int i = 0;
            while (token != NULL) {
                // Verificar si el estudiante está activo
                if (obtenerEstadoEstudiante(token) == 0) {
                    strcpy(cursos[num_cursos].estudiantes[i++].matricula, token);
                }
                token = strtok(NULL, "/");
            }
            cursos[num_cursos].num_estudiantes = i; 

            num_cursos++; 
        }
        fclose(file);
    } else {
        printf("Error al abrir el archivo.\n");
    }}
void guardarCursos() {
    FILE *file = fopen("cursos.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < cursoCount; i++) {
            fprintf(file, "%s-%s-%s-%s-%s",
                    cursos[i].codigo,
                    cursos[i].codigoMateria,
                    cursos[i].ccProfesor,
                    cursos[i].fechaInicio,
                    cursos[i].fechaFin);
            // Guardar las matrículas de los estudiantes activos
            for (int j = 0; j < cursos[i].num_estudiantes; j++) {
                if (j == 0) {
                    fprintf(file, "-%s", cursos[i].matriculasEstudiantes[j]);
                } else {
                    fprintf(file, "/%s", cursos[i].matriculasEstudiantes[j]);
                }
            }
            fprintf(file, "\n"); // Nueva línea al final de cada curso
        }
        fclose(file);
    } else {
        printf("Error al abrir el archivo para guardar los cursos.\n");
    }
}



