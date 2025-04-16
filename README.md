# MecanumWheel735
## 概要
メカナムホイールを制御する．モータは735を使用する．

| 項目         | 仕様             |
| ------------ | ---------------- |
| 使用マイコン | NUCLEO_F446RE    |
| 使用IDE      | CubeIDE,VSCode   |
| 使用言語等   | C++,STM32CubeHAL |

## ピン設定
| ピン | 設定        | ラベル              | 備考           |
| ---- | ----------- | ------------------- | -------------- |
| PA5  | GPIO_Output | DebugLED            | ラベルのみ変更 |
| PC13 | GPIO_EXTI13 | DebugButton         | ラベルのみ変更 |
| PB9  | I2C1_SDA    | I2C1_SDA_BNO        |                |
| PB8  | I2C1_SCL    | I2C1_SCL_BNO        |                |
| PA12 | CAN1_TX     | CAN1_TX_motorDriver |                |
| PA11 | CAN1_RX     | CAN1_RX_motorDriver |                |

## クロック設定
| 項目                   | 内容 | 備考               |
| ---------------------- | ---- | ------------------ |
| APB1 peripheral clocks | 30   | CAN1を使いたかった |

## 変更した設定
### Project Manager
Code Generator, Generated files\
✅Generate peripheral initialization as a pair of '.c/.h' files per peripheral
### USART2
NVIC Settings\
✅USART2 global interrupt
### I2C1
MODE: I2C
#### Parameter Settings
| 項目            | 設定      | 備考                        |
| --------------- | --------- | --------------------------- |
| I2C Speed Mode  | Fast Mode | Standard Modeじゃ無理だった |
| I2C Clock Speed | 400000Hz  | BNO055                      |

その他は変えていない
### CAN1
MODE: ✅Activated\
CAN1で通信する．
#### Parameter Settings
[参考文献](https://hsdev.co.jp/stm32-can/)の通りに設定した．

| 項目                       | 内容  |
| -------------------------- | ----- |
| 転送速度 Baud Rate         | 1Mbps |
| サンプリングポイント       | 80%   |
| Bit Time(Time for one Bit) | 1μs   |
| CANのクロック源            | 30MHz |
| Prescaler                  | 3     |
| Time Quantum               | 100ns |
| TSeg1                      | 7     |
| TSeg2                      | 2     |
| SJW                        | 1     |

## プログラム概要
### setup()
Hello WorldとPCに送信
### loop()
now = HAL_GetTick()
#### 0.1秒ごとに
現在の経過時間をPCに送信\
ボタンが押されていた場合，LEDの点灯/消灯を切り替える
