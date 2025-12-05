# 🎮 ATOMIC RUNNER CHELNOV - ANÁLISIS DE REFERENCIA

## 📊 INFORMACIÓN GENERAL DEL JUEGO

### Datos Básicos
- **Título Original**: Atomic Runner Chelnov (走れ！チェルノブ)
- **Título Alternativo**: "Run, Chelnov! Run!"
- **Desarrollador**: Data East
- **Año de Lanzamiento**: 1988 (Arcade)
- **Plataformas**: Arcade, Mega Drive/Genesis, Amiga
- **Género**: Run and Gun / Side-scrolling Action
- **Inspiración**: Desastre nuclear de Chernobyl (1986)

### Contexto Histórico
El juego fue creado poco después del desastre de Chernobyl, incorporando temática nuclear y de radiación como elemento central de la narrativa. El protagonista es un corredor transformado en superhéroe por la radiación.

---

## 🎯 MECÁNICAS CORE DEL JUEGO

### 1. Movimiento (2.5D Side-Scrolling)

#### Características principales:
- **Auto-scroll constante**: El escenario se mueve automáticamente de izquierda a derecha
- **Movimiento del jugador**: Solo puede moverse dentro del espacio visible de la pantalla
- **No hay movimiento hacia atrás**: El scroll es unidireccional, avanza constantemente
- **Muerte por aplastamiento**: Si el borde izquierdo te alcanza, mueres instantáneamente

#### Restricciones de movimiento:
```
Ejes permitidos:
├─ Horizontal (X): Izquierda/Derecha dentro de límites de pantalla
├─ Vertical (Y): LIMITADO - Solo pequeños ajustes de altura
└─ Salto (Z): Salta sobre enemigos y obstáculos
```

#### Velocidades:
- **Caminar**: Velocidad base estándar
- **Correr**: No hay sprint separado, velocidad constante
- **Salto**: Arco de salto fijo, sin control aéreo avanzado
- **Auto-scroll**: ~60-80 unidades/segundo (ajustable por nivel)

### 2. Sistema de Combate

#### Armas Principales:
1. **Arma inicial**: Proyectil básico (disparo frontal)
2. **Power-ups de armas**:
   - Láser (beam continuo)
   - Misiles (homing missiles)
   - Fuego ondulante (wave beam)
   - Bolas de fuego (fire balls)

#### Mecánica de disparo:
- **Botón de disparo**: Disparo automático continuo al mantener presionado
- **Dirección**: Siempre dispara hacia adelante (derecha)
- **Cadencia**: ~5-8 proyectiles por segundo
- **Limitación**: Máximo 3-4 proyectiles en pantalla simultáneamente

### 3. Sistema de Salud

#### Modelo de salud:
- **Barra de vida**: ~8-10 puntos de salud
- **Damage por golpe**: 1-2 puntos dependiendo del enemigo
- **Sin regeneración**: No se recupera salud automáticamente
- **Ítems de curación**: Power-ups raros que restauran 2-3 puntos

#### Muerte:
- Al llegar a 0 HP → Pierde una vida
- Sin invulnerabilidad post-hit (i-frames muy cortos ~0.5s)

### 4. Sistema de Vidas y Continues

#### Vidas:
- **Vidas iniciales**: 3 vidas
- **Extra lives**: Se obtienen por score (cada 50,000 puntos)
- **Game Over**: Al perder todas las vidas

#### Continues:
- Sistema de créditos arcade (insertar moneda para continuar)
- En versión consola: Continúa desde checkpoint

---

## 🗺️ ESTRUCTURA DE NIVELES

### Diseño de Stages

#### Características generales:
1. **7 Stages totales** en el arcade original
2. **Duración**: 3-5 minutos por stage
3. **Temática progresiva**: Cada nivel tiene tema visual único
4. **Boss al final**: Cada stage termina con boss fight

#### Elementos de nivel:

##### Terreno y Plataformas:
- **Suelo principal**: Plataforma base donde corre el jugador
- **Plataformas elevadas**: Niveles superiores accesibles por salto
- **Plataformas bajas**: Pozos y desniveles
- **Destruibles**: Algunos elementos del entorno son destructibles

##### Obstáculos:
- **Estáticos**: Paredes, bloques, estructuras
- **Móviles**: Plataformas en movimiento
- **Hazards**: Picos, lava, electricidad (kill zones)
- **Destructibles**: Barriles, cajas que pueden contener ítems

##### Background (Parallax):
```
Capas de profundidad:
├─ Capa 1 (fondo lejano): Velocidad × 0.2 (cielo, montañas)
├─ Capa 2 (fondo medio): Velocidad × 0.5 (edificios lejanos)
├─ Capa 3 (fondo cercano): Velocidad × 0.8 (estructuras)
└─ Capa 4 (gameplay): Velocidad × 1.0 (suelo, plataformas)
```

### Lista de Stages:

#### Stage 1: Ciudad Industrial
- **Entorno**: Fábrica, chimeneas, edificios
- **Enemigos**: Soldados básicos, robots pequeños
- **Boss**: Robot tanque grande

#### Stage 2: Base Subterránea
- **Entorno**: Túneles, tuberías, instalaciones
- **Enemigos**: Soldados mejorados, drones
- **Boss**: Mecha volador

#### Stage 3: Selva Contaminada
- **Entorno**: Vegetación mutada, ruinas
- **Enemigos**: Criaturas mutantes, plantas carnívoras
- **Boss**: Bestia gigante mutada

#### Stage 4: Zona Militar
- **Entorno**: Base militar, tanques, helicópteros
- **Enemigos**: Elite soldiers, vehículos blindados
- **Boss**: Helicóptero de combate

#### Stage 5: Reactor Nuclear
- **Entorno**: Interior de planta nuclear, reactores
- **Enemigos**: Robots de seguridad, drones avanzados
- **Boss**: Robot de seguridad masivo

#### Stage 6: Laboratorio
- **Entorno**: Instalación científica, experimentos
- **Enemigos**: Cyborgs, experimentos fallidos
- **Boss**: Científico mutado

#### Stage 7: Confrontación Final
- **Entorno**: Sala de control principal
- **Enemigos**: Elite forces
- **Boss Final**: Líder enemigo con armadura powered

---

## 👾 SISTEMA DE ENEMIGOS

### Tipos de Enemigos

#### 1. Infantería Básica
- **Comportamiento**: Camina hacia el jugador, dispara ocasionalmente
- **HP**: 1-2 hits
- **Ataque**: Proyectil lento frontal
- **Velocidad**: Lenta (50% velocidad jugador)
- **Score**: 100 puntos

#### 2. Soldados de Elite
- **Comportamiento**: Movimiento táctico, disparo frecuente
- **HP**: 3-4 hits
- **Ataque**: Ráfagas de 3 proyectiles
- **Velocidad**: Media (70% velocidad jugador)
- **Score**: 300 puntos

#### 3. Drones Voladores
- **Comportamiento**: Patrón sinusoidal en el aire
- **HP**: 2 hits
- **Ataque**: Disparo diagonal descendente
- **Velocidad**: Rápida (90% velocidad jugador)
- **Score**: 200 puntos

#### 4. Robots Terrestres
- **Comportamiento**: Avanza en línea recta, alto HP
- **HP**: 5-8 hits
- **Ataque**: Melee al contacto o lanzallamas
- **Velocidad**: Muy lenta (30% velocidad jugador)
- **Score**: 500 puntos

#### 5. Vehículos (Mini-bosses)
- **Comportamiento**: Aparece desde el fondo, avanza
- **HP**: 15-20 hits
- **Ataque**: Múltiples torretas, misiles
- **Velocidad**: Match scroll speed
- **Score**: 1000 puntos

### Patrones de Spawn

#### Oleadas:
```
Patrón típico cada 5-10 segundos:
├─ 2-3 enemigos básicos desde la derecha
├─ 1 enemigo volador desde arriba
└─ Cada 30 segundos: Mini-boss o vehículo
```

#### Posiciones de spawn:
- **Borde derecho**: Enemigos terrestres
- **Parte superior**: Enemigos voladores
- **Desde el fondo**: Vehículos grandes

---

## 🎁 SISTEMA DE POWER-UPS

### Tipos de Items

#### 1. Power-ups de Arma
- **Sprite**: Cápsula con símbolo de arma
- **Efecto**: Cambia el tipo de disparo
- **Duración**: Permanente hasta morir o recoger otro
- **Spawn**: Al destruir contenedores o enemigos especiales

#### 2. Ítems de Salud
- **Sprite**: Cruz médica o botiquín
- **Efecto**: Restaura 2-3 puntos de salud
- **Spawn**: Muy raro, al destruir contenedores específicos

#### 3. Power-ups Temporales
- **Invencibilidad**: Estrella, 5 segundos de inmunidad
- **Velocidad**: Botas, incrementa velocidad 50% por 10 segundos
- **Disparo rápido**: Reloj, duplica cadencia por 10 segundos

#### 4. Ítems de Score
- **Medallas**: 500-5000 puntos
- **Joyas**: 1000-10000 puntos
- **Spawn**: Al destruir todos los enemigos de una oleada

### Mecánica de Drop
```
Probabilidad de drop al destruir enemigo:
├─ 70%: Nada
├─ 20%: Score item (100-500)
├─ 8%: Power-up de arma
└─ 2%: Health item
```

---

## 🎨 ESTILO VISUAL Y ARTE

### Resolución Original
- **Arcade**: 256×224 píxeles
- **Sprites**: 16×16 a 32×32 píxeles
- **Bosses**: 64×64 a 128×128 píxeles

### Paleta de Colores
- **Estilo**: Pixel art de 8-bit/16-bit
- **Colores**: Paleta limitada de 256 colores
- **Temática**: Tonos oscuros, industriales, post-apocalípticos
- **Contraste**: Alto contraste para visibilidad en arcade

### Animaciones

#### Personaje Principal (Chelnov):
```
Estados de animación:
├─ Idle: 2-3 frames (respiración)
├─ Run: 4-6 frames (ciclo continuo)
├─ Jump: 3-4 frames (ascenso, pico, descenso)
├─ Shoot: Overlay de 2 frames sobre run/jump
└─ Death: 4-5 frames (explosión)
```

#### Enemigos:
```
├─ Walk: 2-4 frames
├─ Shoot: 2 frames
└─ Death: 3-4 frames (explosión/desintegración)
```

### Efectos Visuales
- **Disparos**: Proyectiles animados de 2 frames
- **Explosiones**: 4-6 frames expansion y fade
- **Daño**: Flash blanco del sprite al recibir daño
- **Power-up**: Partículas brillantes al recoger

---

## 🔊 DISEÑO DE AUDIO

### Música

#### Características:
- **Estilo**: Chiptune/FM Synthesis (Yamaha YM2151)
- **Tempo**: Rápido y enérgico (140-160 BPM)
- **Loop**: Música continua en loop por stage
- **Cambio de intensidad**: Music intensifies cerca de boss

#### Tracks principales:
1. **Title Screen**: Heroico y épico
2. **Stage Theme**: Único por cada nivel
3. **Boss Battle**: Intenso y agresivo
4. **Game Over**: Melancólico
5. **Victory**: Triunfante

### Efectos de Sonido

#### SFX Esenciales:
```
├─ Jump: Whoosh corto
├─ Shoot: Pew/laser sound
├─ Hit Enemy: Impact sound
├─ Take Damage: Pain grunt
├─ Explosion: Boom (3 variantes)
├─ Power-up: Jingle positivo
├─ Death: Explosión grande
└─ Boss Hurt: Heavy impact
```

---

## 🎯 SISTEMA DE SCORING

### Puntuación por Acciones

#### Enemigos:
```
├─ Infantería básica: 100 pts
├─ Soldados elite: 300 pts
├─ Drones: 200 pts
├─ Robots: 500 pts
├─ Mini-boss: 1,000 pts
└─ Boss: 5,000-10,000 pts
```

#### Bonus:
```
├─ Destruir objeto destructible: 50 pts
├─ Recoger item de score: 500-5,000 pts
├─ Completar stage sin morir: 10,000 pts
├─ No damage bonus (stage): 20,000 pts
└─ Time bonus: Restante × 100
```

### High Score
- **Tabla de puntuaciones**: Top 10
- **Iniciales**: 3 letras
- **Score máximo**: ~999,999 puntos

---

## 🎮 DIFICULTAD Y BALANCE

### Curva de Dificultad

#### Progresión por Stage:
```
Stage 1: Tutorial suave, enemigos lentos
Stage 2: Introducción de enemigos voladores
Stage 3: Incremento de velocidad de scroll
Stage 4: Múltiples tipos de enemigos simultáneos
Stage 5: Hazards ambientales + enemigos densos
Stage 6: Enemigos elite + scroll muy rápido
Stage 7: Boss rush + final challenge
```

### Ajustes por Dificultad (Arcade DIP switches)

#### Easy:
- Vidas iniciales: 5
- Damage: 0.5× multiplicador
- Enemy HP: 0.7×
- Spawn rate: 0.8×

#### Normal:
- Vidas iniciales: 3
- Damage: 1.0×
- Enemy HP: 1.0×
- Spawn rate: 1.0×

#### Hard:
- Vidas iniciales: 2
- Damage: 1.5×
- Enemy HP: 1.2×
- Spawn rate: 1.3×

---

## 🔧 CONSIDERACIONES TÉCNICAS (Arcade Original)

### Hardware Arcade
- **CPU**: Motorola 68000 @ 10MHz
- **Sound CPU**: MOS 6502 @ 1.5MHz
- **Sound Chip**: YM2151 + YM3012 (DAC)
- **Display**: Raster, 256×224, 60Hz
- **Colors**: 1024 colores disponibles, 256 on-screen

### Limitaciones Técnicas (Que inspiran diseño)
```
├─ Sprites en pantalla: Máximo 64 simultáneos
├─ Tamaño sprite: 8×8 a 32×32 píxeles
├─ Layers: 3 capas de scrolling
├─ Memoria de video: 64KB
└─ ROM del juego: 512KB
```

---

## 📝 ADAPTACIÓN PARA UNREAL ENGINE 5.3

### Mantener del Original:
1. ✅ **Auto-scroll constante** (core mechanic)
2. ✅ **Movimiento restringido a pantalla visible**
3. ✅ **Sistema de vidas y game over**
4. ✅ **Power-ups de armas**
5. ✅ **Boss fights al final de stage**
6. ✅ **Estilo visual pixel art/retro**

### Modernizar/Adaptar:
1. 🔄 **Resolución**: 1920×1080 manteniendo estilo pixel art
2. 🔄 **Animaciones**: Más frames para suavidad
3. 🔄 **Parallax**: Mayor profundidad (5+ capas)
4. 🔄 **Partículas**: Efectos modernos pero retro-styled
5. 🔄 **Post-processing**: Scanlines, CRT effect opcional
6. 🔄 **Control**: Soporte para gamepad moderno

### Simplificar (Para prototipo académico):
1. ⚠️ **Auto-scroll**: Opcional/configurable
2. ⚠️ **Boss fights**: 1-2 bosses simples
3. ⚠️ **Número de stages**: 2-3 niveles funcionales
4. ⚠️ **Tipos de enemigos**: 3-4 tipos básicos
5. ⚠️ **Sistema de armas**: 2-3 tipos de disparo

---

## 🎓 APLICACIÓN AL PROYECTO ACADÉMICO

### Prioridades de Implementación

#### FASE 1: Core Mechanics (COMPLETADO ✅)
- [x] Personaje 2.5D con movimiento lateral
- [x] Cámara side-scrolling fija
- [x] Sistema de salud
- [x] Kill volumes
- [x] Health pickups

#### FASE 2: Gameplay Básico (SIGUIENTE)
- [ ] Auto-scroll opcional del nivel
- [ ] Sistema de disparo básico
- [ ] 1-2 tipos de enemigos simples
- [ ] Spawn de enemigos por tiempo
- [ ] Collision jugador-enemigo

#### FASE 3: Polish y Content
- [ ] Power-ups de arma (1-2 tipos)
- [ ] Animaciones del personaje
- [ ] Efectos visuales (disparos, explosiones)
- [ ] Background parallax
- [ ] Música y SFX

#### FASE 4: Advanced (Opcional)
- [ ] Boss fight simple
- [ ] Sistema de score
- [ ] Multiple stages
- [ ] Checkpoint system

---

## 📚 REFERENCIAS ÚTILES

### Recursos de Investigación:
1. **Videos de gameplay**: YouTube "Atomic Runner Chelnov longplay"
2. **Sprite sheets**: Spriters Resource - Atomic Runner
3. **Música**: Zophar's Domain - Arcade soundtracks
4. **Manuales**: Arcade manuals (PDF scans)

### Assets Actuales del Proyecto:
```
Content/BackGround/
├─ Atomic_Runner sprites (múltiples stages)
├─ Tilesets para niveles
└─ Background layers para parallax
```

---

## 🎯 CONCLUSIONES CLAVE PARA DESARROLLO

### 1. Filosofía de Diseño:
> "Constante movimiento hacia adelante, presión constante, reacción rápida"

### 2. Pilares Mecánicos:
- **Movimiento**: Simple pero preciso (2.5D lateral)
- **Combate**: Disparo continuo, gestión de power-ups
- **Supervivencia**: Evitar enemigos Y obstáculos simultáneamente
- **Presión**: Auto-scroll no perdona, empuja al jugador

### 3. Feel del Juego:
- **Ritmo**: Frenético pero controlable
- **Recompensa**: Cadena de kills = satisfacción
- **Riesgo**: Balance entre avanzar y sobrevivir
- **Skill**: Memorización de patrones + reflejos

### 4. Adaptación C++/Blueprint:
```
C++ Base (Performance crítico):
├─ Movimiento y física
├─ Sistema de proyectiles
├─ Collision detection
└─ Spawn management

Blueprint (Content y balance):
├─ Enemy behaviors específicos
├─ Power-up effects
├─ Level scripting
└─ Boss patterns
```

---

## 📊 MÉTRICAS DE REFERENCIA

### Timing y Velocidades (Para implementación UE5):
```
Player Movement:
├─ Walk Speed: 300 units/s (Unreal)
├─ Run Speed: 600 units/s
├─ Jump Height: 200 units
└─ Jump Duration: ~0.8 seconds

Auto-Scroll:
├─ Stage 1-2: 100 units/s
├─ Stage 3-4: 150 units/s
└─ Stage 5-7: 200 units/s

Enemy Speed:
├─ Slow: 150 units/s (robots)
├─ Medium: 300 units/s (soldiers)
└─ Fast: 450 units/s (drones)
```

### Distances y Spacing:
```
Screen Bounds:
├─ Width: 1920 units (1080p)
├─ Safe Zone: 300 units cada lado
└─ Death Zone: -100 units (left border)

Enemy Spawn:
├─ Spawn ahead: +2000 units (derecha)
├─ Spawn above: +800 units (arriba)
└─ Despawn behind: -500 units (izquierda)
```

---

**Documento de investigación completado - Última actualización: Diciembre 4, 2025**
**Versión: 1.0 - Base de conocimiento para desarrollo del proyecto PocketMirrorV2**
