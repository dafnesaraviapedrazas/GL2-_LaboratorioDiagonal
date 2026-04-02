# Laboratorio: Movimiento en 8 Direcciones/Diagonal - Unreal Engine 4.27

## 📌 Objetivo

Adaptar un script de tipo Pawn para que el personaje pueda moverse tanto en las 4 direcciones básicas como en diagonales, manteniendo una velocidad constante en todos los casos.

## ✨ ¿Qué hace?

- Movimiento ortogonal: ↑ ↓ ← →
- Movimiento diagonal: ↗ ↖ ↘ ↙
- Velocidad uniforme gracias a un factor de corrección

## ⚙️ ¿Cómo funciona?

Se creó una función llamada `ManejarDireccionDiagonal` que recibe la dirección actual (definida en un enumerador) y el tiempo entre frames. Dentro de ella, se usa un `switch` para determinar qué vector de movimiento corresponde.

### El truco de las diagonales

Si sumas dos direcciones normales (ej. derecha + arriba), el personaje se mueve más rápido de lo debido por el teorema de Pitágoras (√2 ≈ 1.41). Para evitarlo, se multiplica por **0.707** (que es 1/√2), logrando que la diagonal avance igual que los ejes simples.

```cpp
// Ejemplo para diagonal arriba-derecha
case EMoveDirection::UpRight:
    MovementStep = FVector(0.707f, 0.707f, 0.0f);
    break;
