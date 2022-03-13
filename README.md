# VisualMemory
### Opis założeń.
Projekt ma być odwzorowaniem testu na pamięc wizualną człowieka.Układ będzie złożony z przycisków 6x6 z podświetlaniem LED oraz wyświetlacza LCD, wyświetlający wynik testu. Inspiracją jest test, który można znaleźć na stronie www.humanbenchmark.com.

### Analiza zadania - wybór elementów elektronicznych i narzędzi użytych do realizacji projektu.

Podstawowe elementy jakie muszą znaleźć się w układzie:
- mikroprocesor
- wyświetlacz
- 36 przycisków
- zasilacz
- diody LED

**Diody** - wybrany został pasek LED ws2812b, ponieważ jest bardzo prosty w użyciu, łatwy do podłączenia oraz do zaprogramowania. Ponadto na pasku LED znajduje się odpowiednio dużo diod LED, które można odcinać od reszty, a następnie za pomocą przewodów łączyć je z powrotem.

**Wyświetlacz** - dobrym wyborem był tutaj wyświetlacz LCD 16x2, ponieważ wyświetlanych informacji nie ma aż tak wiele, więc taka wielkość wystarczy.

**Zasilacz** - 5V zasilacz sieciowy jest tutaj odpowiedni ponieważ do poprawnego działania wybranych elementów potrzebne jest takie napięcie, możliwe byłoby również zasilanie przez USB, gdybyśmy chcieli użyć tego urządzenia jako kontroler MIDI, jednakże mogłoby to się wiązać z problemami w przypadku dużej ilości diod LED jednocześnie, ponieważ wymaga to dosyć sporej mocy.

**Przyciski** - tactile switch są tu w zupełności wystarczające przy założeniu, że projekt nie wymaga od nas dużej precyzji (tzn. szybkiego naciskania przycisków).

**Atmega328P-PU** - mikroprocesor AVR jest tutaj dobrym wyborem, ponieważ IDE, którym jest Arduino dostarcza nam proste w użyciu i intuicyjne biblioteki dla wybranych wcześniej komponentów. Dodatkowo warto zauważyć, że ilość pinów w tym procesorze idealnie pasuje do tego układu. Z pinów analogowych możemy korzystać jak z pinów cyfrowych po ustawieniu odpowiedniego trybu, dzięki temu nie trzeba się martwić o brak pinów cyfrowych

**Inne potrzebne elementy:**
- zestaw rezystorów
- diody 1N4007 - przydatne w klawiaturach matrycowych do eliminacji przekłamań
- zestaw kondensatorów
- potencjometr - dzięki niemu dostosować można kontrast na wyświetlaczu LCD
- płytka PCB
- kable
- perfboard (DOT PCB) - na nim będzie zbudowana cała konstrukcja (przyciski i diody LED)

### Specyfikacja wewnętrzna urządzenia.
**Schemat blokowy i ideowy urządzenia**

![schemat-blokowy](https://github.com/Wojwos/VisualMemory/blob/main/img/schemat-blokowy.jpg?raw=true)

![schemat-ideowy](https://github.com/Wojwos/VisualMemory/blob/main/img/schematic.jpg?raw=true)

**Opis funkcji poszczególnych bloków układu, szczegółowy opis działania ważniejszych elementów układu**
Klawiatura matrycowa składa się z 36 przycisków, do każdego przycisku przyporządkowane dwie diody LED, ponieważ są gęsto rozstawione na pasku WS2812B. Klawiatura podłączona do reszty urządzenia z wyświetlaczem LCD, na którym wyświetlone są wszystkie informacje.

![dot-pcb](https://github.com/Wojwos/VisualMemory/blob/main/img/dot-pcb.jpg?raw=true)

**Schemat montażowy obejmujący projekt płytki drukowanej, rozmieszczenie elementów na płytce oraz rozmieszczenie elementów urządzenia w obudowie**

![schemat-montazowy](https://github.com/Wojwos/VisualMemory/blob/main/img/board.jpg?raw=true)

**Lista elementów:**

Elementy na płytce PCB:
- Atmega328P-PU
- wyświetlacz LCD 16x2
- 2x rezystor 10k
- 6x dioda 1N4007
- 2x kondensator 100nF
- potencjometr
- gniazdo do zasilacza 5V

Elementy poza płytką (umieszczone na perfboardzie):
- 36x tactile switch
- 72x LED WS2812B

**Algorytm oprogramowania urządzenia, w tym schemat blokowy**

![algorytm](https://github.com/Wojwos/VisualMemory/blob/main/img/algorytm.jpg?raw=true)

### Specyfikacja zewnętrzna urządzenia:
**Opis funkcji elementów sterujących urządzeniem**
Urządzeniem sterujemy wyłącznie za pomocą przycisków według instrukcji wyświetlanych na wyświetlaczu LCD. Przycisków łącznie jest 36. Czasami program wymaga od nas naciśnięcia odpowiednich przycisków, a czasem dowolnego w celu kontynuowania.

**Opis funkcji elementów wykonawczych (wyświetlacz, diody LED,**
przekaźniki)
Wyświetlacz informuje nas o wyniku, poziomie, oraz co należy zrobić.

**Opis reakcji oprogramowania na zdarzenia zewnętrzne**
Oprogramowanie odczytuje stan 36 przycisków podczas fazy zgadywania.

**Skrócona instrukcja obsługi urządzenia**
Urządzenie należy podłączyć do prądu, następnie wszystkie informacje zostaną wyświetlone na wyświetlaczu LCD takie jak:
- Naciśnij dowolny przycisk aby kontynuować
- Zapamiętaj podświetlone pole (mamy na to 3 sekundy)
- Zgadnij wszystkie pola (wyświetlona ilość pól odgadniętych i pól łącznie do odgadnięcia) - po wyświetleniu tej informacji naciskamy zapamiętane pola dopóki nie odgadniemy wszystkich lub stracimy wszystkie 3 życia
- Gratulacje! kontynuuj (musimy przycisnąć dowolny przycisk), kolejny poziom: ? - w zależności ile razy udało nam się odgadnąć wszystkie pola nie tracąc wszystkich żyć

**Opis złączy i/lub schematu okablowania**
Kable wychodzą ze skrzynki z układem scalonym do klawiatury (6 kabli do kolumn, 6 kabli do wierszy, 3 kable do diod LED)

**Opis montażu układu**
Układ scalony znajduje się w skrzynce z wbudowanym wyświetlaczem LCD, klawiatura oraz diody LED znajdują się na oddzielnym perfboardzie.

**Opis sposobu programowania układu**
Oprogramowanie zostało stworzone w Arduino IDE z wykorzystaniem bibliotek obsługujących klawiaturę matrycową, wyświetlacz LCD oraz diody LED ws2812b.

### Działanie

![test1](https://github.com/Wojwos/VisualMemory/blob/main/img/test1.jpg?raw=true)

![test2](https://github.com/Wojwos/VisualMemory/blob/main/img/test2.jpg?raw=true)

![test3](https://github.com/Wojwos/VisualMemory/blob/main/img/test3.jpg?raw=true)

![test4](https://github.com/Wojwos/VisualMemory/blob/main/img/test4.jpg?raw=true)

![test5](https://github.com/Wojwos/VisualMemory/blob/main/img/test5.jpg?raw=true)

![test6](https://github.com/Wojwos/VisualMemory/blob/main/img/test6.jpg?raw=true)
