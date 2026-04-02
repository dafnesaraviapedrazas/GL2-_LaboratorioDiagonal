# Laboratorio: Creación de Script para Movimiento Diagonal

Este proyecto consiste en la modificación de un Actor Pawn en Unreal Engine 4.27 para permitir el desplazamiento en 8 direcciones (ortogonales y diagonales) mediante el uso de enumeradores y lógica de normalización de vectores.

## 🚀 Funcionalidades

- Movimiento arriba, abajo, izquierda y derecha.
- Movimiento diagonal (Arriba-Derecha, Arriba-Izquierda, Abajo-Derecha, Abajo-Izquierda).
- Velocidad constante en diagonal mediante normalización.

## 🛠️ Detalles Técnicos

La implementación se basa en la clase `ATopDownMover`. El núcleo de la lógica reside en la función `ManejarDireccionDiagonal`, donde se evalúa el enumerador `EMoveDirection`.

### Normalización del Vector

Para evitar que el objeto se mueva más rápido al combinar dos ejes (Efecto Pitágoras), se aplicó un factor de magnitud de `0.707` (1/√2) en las direcciones diagonales:

```cpp
case EMoveDirection::UpRight:
    MovementStep = FVector(0.707f, 0.707f, 0.0f);
    break;
