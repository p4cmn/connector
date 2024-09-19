# COM Port Communication Application

## Описание

**COM Port Communication Application** — это приложение, написанное на Qt C++, которое позволяет пользователю вводить данные в один COM-порт и получать данные из другого COM-порта. Приложение также предоставляет интерфейс для настройки параметров COM-портов и отображения текущих параметров.

### Основные функции:
- Отправка данных в выбранный COM-порт.
- Прием данных из другого COM-порта.
- Настройка параметров COM-портов (скорость передачи данных, биты данных, стоп-биты, четность и т.д.).
- Просмотр текущих параметров COM-портов в отдельном окне.

## Технические детали

- **Язык программирования**: C++ с использованием библиотеки **Qt**.
- **Операционная система**: Windows.
- **Архитектура**: Приложение построено на основе паттерна **MVC** (Model-View-Controller).

### Архитектурные компоненты

1. **Model (Модель)**:
   - Хранит данные о текущих настройках COM-портов и данные, отправленные через порт.
   - Реализует логику взаимодействия с низкоуровневыми библиотеками для работы с COM-портами (например, через WinAPI).

2. **View (Представление)**:
   - Графический интерфейс для пользователя с возможностью настройки параметров COM-портов.
   - Ввод данных для отправки в COM-порт и просмотр принятых данных.

3. **Controller (Контроллер)**:
   - Управляет взаимодействием между моделью и представлением.
   - Передает данные от представления в модель для отправки через COM-порт.
   - Обновляет представление по мере изменения данных в модели (например, когда приняты новые данные из порта).
