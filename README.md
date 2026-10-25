# Taller 2: Estructura de Datos | Hospital Marmaja

Este proyecto es una continuación del Taller 1, desarrollado en C++. Se implementó un sistema hospitalario que permite cargar pacientes desde un archivo, clasificarlos mediante un árbol de decisión y almacenarlos en árboles AVL según el departamento asignado.

## Integrantes
- **Nombre:** Ignacio Valdivia Rodriguez
- **RUT:** 22.179.357-9
- **GitHub:** @nchq7
- **Carrera:** ICCI
- **Paralelo:** C1 (Bastián Ruiz)

## Arquitectura del Proyecto

El código está organizado en carpetas para separar las clases de su implementación:

- `include/`: Archivos `.h`, separados en `dominio/` y `logica/`.
- `src/`: Archivos `.cpp` y `main.cpp`.
- `datos/`: Archivo `pacientes.txt` utilizado para cargar los pacientes.

## Funcionamiento del Sistema

El programa carga los pacientes en una **Queue implementada manualmente**, respetando el orden FIFO. Luego, un árbol binario de decisión evalúa sus atributos y determina el servicio correspondiente.

El árbol utiliza las siguientes prioridades: cirugía, síntomas neurológicos, trauma, urgencias (temperatura >= 38.5 o dolor >= 8), dolor de pecho, edad menor a 14 años y hospitalización de al menos 2 días. Si ninguna condición se cumple, se asigna Medicina General.

Este orden permite resolver casos donde un paciente cumple varias condiciones, dando prioridad a la primera que resulte verdadera. Los criterios son una simplificación académica y no un protocolo médico.

Cada servicio tiene su propio **árbol AVL ordenado por ID**, que permite insertar, buscar y eliminar pacientes, además de realizar recorridos y rotaciones para mantener el balance.

El sistema también controla datos inválidos, archivos inexistentes e IDs duplicados.

## Instrucciones de Compilación y Ejecución

Para ejecutar el programa se necesita un compilador G++ compatible con C++17. Abrir la terminal desde la carpeta principal del proyecto.

**Compilación en Windows:**

```powershell
g++ -std=c++17 -Iinclude src/main.cpp src/dominio/Paciente.cpp src/logica/ColaPacientes.cpp src/logica/LectorPacientes.cpp src/logica/ArbolDecision.cpp src/logica/ArbolAVL.cpp src/logica/Hospital.cpp -o hospital.exe
```

**Ejecución:**

```powershell
.\hospital.exe
```

**Compilación y ejecución en Codespaces (Linux):**

```bash
g++ -std=c++17 -Iinclude src/main.cpp src/dominio/Paciente.cpp src/logica/*.cpp -o hospital
./hospital
```

El archivo `datos/pacientes.txt` debe estar presente y el programa debe ejecutarse desde la raíz del proyecto.

## Opciones del Menú

1. Atender pacientes.
2. Ver departamentos y recorridos AVL.
3. Buscar pacientes por ID o nombre.
4. Eliminar pacientes.
5. Salir.
