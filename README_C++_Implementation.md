# PocketMirrorV2 - 2.5D Side-Scrolling Runner

## 📋 Descripción del Proyecto

Proyecto académico de Unreal Engine 5.3 - Prototipo 2.5D inspirado en "Atomic Runner Chelnov".
El jugador corre de izquierda a derecha con movimiento restringido a un solo eje y cámara lateral fija.

---

## 🏗️ Arquitectura del Proyecto

Este proyecto usa una **arquitectura híbrida C++/Blueprint**:
- **C++ Base**: Clases base limpias y documentadas que definen funcionalidad core
- **Blueprints**: Heredan de C++ para personalización visual y lógica de gameplay

### ✅ Ventajas de esta arquitectura:
1. **Rendimiento**: Código crítico en C++ (movimiento, física, salud)
2. **Flexibilidad**: Diseñadores pueden modificar comportamiento en Blueprints
3. **Educativo**: Código C++ sirve como referencia de buenas prácticas
4. **Mantenible**: Separación clara entre lógica base y contenido

---

## 📁 Estructura de Clases C++

### 1. **ARunner2DCharacter** (Runner2DCharacter.h/cpp)
**Propósito**: Personaje base para movimiento 2.5D

**Características principales**:
- ✅ Movimiento restringido a un solo eje horizontal (X)
- ✅ Cámara lateral fija (side-view)
- ✅ Soporte para Enhanced Input System
- ✅ Velocidades configurables (caminar/correr)
- ✅ Sistema de salto

**Cómo usar en Blueprint**:
```
1. Crear Blueprint: Content Browser → Click derecho → Blueprint Class
2. Buscar "Runner2DCharacter" como clase padre
3. Nombrar: BP_PlayerCharacter
4. Configurar:
   - Mesh/Sprite para el personaje
   - Walk Speed / Run Speed
   - Input Actions
   - Animaciones (Animation Blueprint)
```

**Variables expuestas a Blueprint**:
- `WalkSpeed` (float): Velocidad al caminar
- `RunSpeed` (float): Velocidad al correr
- `bIsRunning` (bool): ¿Está corriendo actualmente?

---

### 2. **UHealthComponent** (HealthComponent.h/cpp)
**Propósito**: Componente reutilizable para gestionar salud de cualquier actor

**Características principales**:
- ✅ Sistema de salud actual/máxima
- ✅ Funciones de daño y curación
- ✅ Eventos para cambios de salud y muerte
- ✅ Porcentaje de salud para barras de UI

**Cómo usar en Blueprint**:
```
1. Abrir BP_PlayerCharacter
2. Panel Components → Add Component → Health Component
3. En Event Graph:
   - Bind a "On Health Changed" para actualizar UI
   - Bind a "On Death" para lógica de muerte
```

**Funciones principales**:
- `TakeDamage(float)`: Aplicar daño
- `Heal(float)`: Restaurar salud
- `GetHealthPercent()`: Obtener % para UI (0.0 - 1.0)
- `ResetHealth()`: Restaurar salud al máximo

**Eventos Blueprint**:
- `OnHealthChanged(Health, MaxHealth, Delta)`: Se dispara al cambiar salud
- `OnDeath()`: Se dispara cuando salud llega a 0

---

### 3. **AHealthPickup** (HealthPickup.h/cpp)
**Propósito**: Actor pickup que cura al jugador por overlap

**Características principales**:
- ✅ Curación al hacer overlap con personaje
- ✅ Sistema de respawn opcional
- ✅ Eventos Blueprint para efectos visuales/audio
- ✅ Configurable por instancia

**Cómo usar en Blueprint**:
```
1. Crear Blueprint heredando de HealthPickup
2. Nombrar: BP_HealthPickup
3. Configurar mesh/sprite en PickupMesh component
4. Ajustar propiedades:
   - Heal Amount: Cantidad de curación
   - Should Respawn: ¿Reaparece después?
   - Respawn Delay: Tiempo de respawn
5. Implementar eventos:
   - OnPickupCollected: Sonido/partículas de recolección
   - OnPickupRespawned: Efecto de spawn
```

**Variables configurables**:
- `HealAmount` (float): Cantidad de salud que restaura
- `bShouldRespawn` (bool): ¿Reaparece después de ser recogido?
- `RespawnDelay` (float): Segundos antes de reaparecer

---

### 4. **AKillVolume** (KillVolume.h/cpp)
**Propósito**: Volumen que mata/daña al jugador y lo teletransporta a PlayerStart

**Características principales**:
- ✅ Mata o daña al jugador
- ✅ Teletransporta a PlayerStart automáticamente
- ✅ Delay configurable para respawn
- ✅ Eventos Blueprint para efectos de muerte

**Cómo usar en Blueprint**:
```
1. Crear Blueprint heredando de KillVolume
2. Nombrar: BP_KillVolume
3. Ajustar tamaño del Kill Box component
4. Configurar propiedades:
   - bInstantKill: true para matar instantáneamente
   - DamageAmount: Daño si no es instant kill
   - bRespawnAtPlayerStart: Auto-respawn
   - RespawnDelay: Delay antes de respawn
5. Colocar en nivel (debajo de plataformas, en precipicios, etc.)
6. Asegurar que hay un PlayerStart en el nivel
```

**Variables configurables**:
- `bInstantKill` (bool): Mata instantáneamente
- `DamageAmount` (float): Daño si no es instant kill
- `bRespawnAtPlayerStart` (bool): Auto-teletransporte
- `RespawnDelay` (float): Segundos antes de respawn

---

### 5. **ARunner2DGameMode** (Runner2DGameMode.h/cpp)
**Propósito**: GameMode base para gestionar reglas del juego

**Características principales**:
- ✅ Sistema de puntuación
- ✅ Control de estado del juego (activo/finalizado)
- ✅ Eventos Blueprint para cambios de estado

**Cómo usar en Blueprint**:
```
1. Crear Blueprint heredando de Runner2DGameMode
2. Nombrar: BP_Runner2DGameMode
3. Configurar Default Pawn Class = BP_PlayerCharacter
4. Implementar eventos:
   - OnScoreChanged: Actualizar UI de score
   - OnGameStarted: Iniciar música, timers, etc.
   - OnGameEnded: Mostrar pantalla de Game Over
5. En Project Settings → Maps & Modes:
   - Establecer como GameMode por defecto
```

**Funciones principales**:
- `AddScore(int32)`: Sumar puntos
- `GetScore()`: Obtener puntuación actual
- `StartGame()`: Iniciar juego
- `EndGame()`: Terminar juego

---

## 🎮 Guía de Implementación

### Paso 1: Compilar el código C++
```bash
1. Cerrar Unreal Editor si está abierto
2. Click derecho en PocketMirrorV2.uproject
3. Seleccionar "Generate Visual Studio project files"
4. Abrir PocketMirrorV2.sln en Visual Studio
5. Build → Build Solution (Ctrl+Shift+B)
6. Esperar a que compile sin errores
7. Abrir el proyecto desde el .uproject
```

### Paso 2: Crear Blueprints base

#### A) Crear BP_PlayerCharacter
1. Content Browser → Blueprints → Click derecho → Blueprint Class
2. Buscar "Runner2DCharacter" → Seleccionar
3. Nombrar: `BP_PlayerCharacter`
4. Abrir el Blueprint:
   - **Components**: Agregar `HealthComponent`
   - **Mesh**: Agregar Skeletal/Static Mesh o Paper Flipbook
   - **Input**: Configurar `DefaultMappingContext`, `MoveAction`, `JumpAction`
   - **Event Graph**: Implementar lógica de animaciones

#### B) Crear Input Actions (Enhanced Input)
1. Content Browser → Input → Click derecho → Input Action
2. Crear:
   - `IA_Move` (Value Type: Axis1D Float)
   - `IA_Jump` (Value Type: Digital Bool)
3. Crear Input Mapping Context:
   - `IMC_Default`
   - Mapear teclas: A/D o Left/Right para Move, Space para Jump

#### C) Crear BP_HealthPickup
1. Heredar de `HealthPickup`
2. Configurar mesh (sphere, coin, heart, etc.)
3. Implementar eventos `OnPickupCollected` con sonido/partículas

#### D) Crear BP_KillVolume
1. Heredar de `KillVolume`
2. Ajustar tamaño del Box Component
3. Colocar debajo del nivel/en precipicios

#### E) Crear BP_Runner2DGameMode
1. Heredar de `Runner2DGameMode`
2. Establecer `Default Pawn Class` = `BP_PlayerCharacter`
3. Implementar `OnScoreChanged` para actualizar UI

### Paso 3: Crear UI (Widgets)

#### Widget: WBP_GameHUD
1. Content Browser → UI → Widget Blueprint
2. Nombrar: `WBP_GameHUD`
3. Diseño:
   - **Progress Bar** para salud (bind a HealthComponent.GetHealthPercent)
   - **Text Block** para score
   - **Text Block** para tiempo (opcional)

4. En BP_PlayerCharacter → Event BeginPlay:
```
Create Widget (WBP_GameHUD) → Add to Viewport
```

#### Widget: WBP_MainMenu
1. Crear Widget: `WBP_MainMenu`
2. Diseño:
   - Background Image
   - **Button "Play"** → OnClicked → Open Level (nombre del nivel de juego)
   - **Button "Exit"** → OnClicked → Quit Game
   - Logo del juego
   - Agregar música de fondo (en Level Blueprint o GameMode)

### Paso 4: Configurar niveles

#### Nivel: MainMenu
1. Crear nivel: `Content/Maps/MainMenu`
2. Crear GameMode especial: `BP_MenuGameMode`
3. En World Settings → GameMode Override = `BP_MenuGameMode`
4. Level Blueprint:
```
Event BeginPlay → 
  Set Show Mouse Cursor (true) →
  Create Widget (WBP_MainMenu) →
  Add to Viewport
```

#### Nivel: GameLevel
1. Crear nivel: `Content/Maps/GameLevel`
2. Colocar **PlayerStart** actor
3. Construir nivel con plataformas
4. Colocar BP_KillVolume debajo de plataformas
5. Colocar BP_HealthPickup en el nivel
6. En World Settings → GameMode Override = `BP_Runner2DGameMode`

### Paso 5: Configurar Project Settings
1. **Edit → Project Settings**
2. **Maps & Modes**:
   - Default GameMode: `BP_Runner2DGameMode`
   - Editor Startup Map: `MainMenu`
   - Game Default Map: `MainMenu`
3. **Input**:
   - Default Mapping Context: `IMC_Default`

---

## 🎯 Requisitos Cumplidos

| Requisito | Estado | Implementación |
|-----------|--------|----------------|
| ✅ Unreal Engine 5.3 | Completo | .uproject configurado |
| ✅ Código C++ limpio y comentado | Completo | 5 clases C++ documentadas |
| ✅ Movimiento 2.5D (1 eje) | Completo | Runner2DCharacter con constraint |
| ✅ Cámara lateral fija | Completo | SpringArm + Camera lateral |
| ✅ Animaciones (Idle/Walk/Run/Jump) | Base C++ lista | Implementar en Animation BP |
| ✅ Kill Volume + respawn | Completo | KillVolume con teleport a PlayerStart |
| ✅ Healing Item | Completo | HealthPickup con overlap |
| ✅ Sistema de Salud | Completo | HealthComponent reutilizable |
| ✅ HUD con barra de salud | Plantilla lista | Crear WBP_GameHUD |
| ✅ Menú principal | Plantilla lista | Crear WBP_MainMenu |
| ✅ Arquitectura Blueprint-friendly | Completo | Clases C++ exponen eventos/propiedades |

---

## 📚 Convenciones de Código

### Nomenclatura
- **Clases C++**: PascalCase sin prefijo (ej: `Runner2DCharacter`)
- **Blueprints**: Prefijo BP_ (ej: `BP_PlayerCharacter`)
- **Widgets**: Prefijo WBP_ (ej: `WBP_GameHUD`)
- **Input Actions**: Prefijo IA_ (ej: `IA_Move`)
- **Variables miembro**: PascalCase con tipo (ej: `bIsActive`, `MaxHealth`)
- **Funciones**: PascalCase verbo + sustantivo (ej: `TakeDamage`, `GetHealthPercent`)

### Comentarios
- Cada clase tiene comentario de propósito
- Funciones públicas documentadas
- Variables importantes explicadas
- TODO: para código pendiente

---

## 🚀 Próximos Pasos (Extensiones opcionales)

1. **Sistema de Enemigos**:
   - Crear `AEnemy2D` base class en C++
   - AI básica con patrullaje
   - Collision con jugador

2. **Sistema de Puntuación**:
   - Pickups de puntos
   - Multiplicadores
   - Tabla de puntuaciones

3. **Parallax Background**:
   - Múltiples capas de fondo
   - Movimiento a diferentes velocidades
   - Ya tienes assets de Atomic Runner

4. **Power-ups**:
   - Velocidad aumentada
   - Invencibilidad temporal
   - Doble salto

5. **Audio**:
   - Música de fondo en loop
   - Efectos de sonido
   - Audio Manager

---

## 🛠️ Troubleshooting

### Error: "Cannot find HealthComponent"
- Compilar proyecto en Visual Studio
- Regenerar project files
- Reiniciar Unreal Editor

### Error: "PlayerStart not found"
- Verificar que hay un PlayerStart en el nivel
- Revisar que KillVolume.bRespawnAtPlayerStart = true

### Personaje no se mueve
- Verificar Input Actions configurados
- Revisar DefaultMappingContext asignado
- Comprobar que Controller está asignado

### Cámara no es lateral
- Revisar CameraBoom rotation (-90° en Yaw)
- Verificar que SpringArm está configurado correctamente

---

## 👥 Créditos

**Proyecto Académico - Unreal Engine 5.3**
- Arquitectura C++/Blueprint híbrida
- Inspirado en "Atomic Runner Chelnov"
- Código educativo con comentarios extensos

---

## 📄 Licencia

Proyecto académico - Uso educativo únicamente
Assets de Atomic Runner con fines educativos/demostración
