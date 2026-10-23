# Warriors

Agentowy symulator starć historycznych. Projekt ma badać wpływ zachowania
żołnierzy, formacji i dowodzenia na przebieg oraz wynik bitwy.

Pierwszy planowany model dotyczy wojskowości napoleońskiej. Rozwój zaczynamy
od starcia dwóch oddziałów piechoty na mapie 2D. Kolejne kroki obejmą morale,
kawalerię, artylerię i koordynację całej armii. W przyszłości wspólny rdzeń
ma obsługiwać osobne reguły i scenariusze dla kilku epok.

## Stan projektu

Repozytorium zawiera początkową strukturę i uruchamialny szkielet aplikacji.
Mechanika symulacji, wczytywanie scenariuszy i wizualizacja nie są jeszcze
zaimplementowane. Program na razie wypisuje komunikat startowy.

## Technologie

- **C++20** — rdzeń symulacji i aplikacja uruchamiana z terminala.
- **CMake 3.20+** — konfiguracja budowania.
- **Python 3.11+ i uv** — środowisko narzędziowe, analiza wyników
  i automatyzacja eksperymentów. Domyślny interpreter: Python 3.13.
- **Ninja** — wykonanie budowania skonfigurowanego przez CMake.
- **Conan** — wybrany menedżer zewnętrznych bibliotek C++.
- **JSON** — wybrany format scenariuszy; wczytywanie zostanie zaimplementowane.

Na obecnym etapie aplikacja nie ma zewnętrznych zależności C++.
Bibliotekę JSON oraz narzędzia wizualizacji dobierzemy przy implementacji.
Conana podłączymy przy dodawaniu pierwszej zewnętrznej biblioteki C++;
obecna konfiguracja budowania jeszcze go nie używa.

## Architektura C++ i Python

**C++ odpowiada za silnik symulacji**: stan świata, kroki czasu, agentów,
ruch, walkę i rozkazy. Silnik jest osobnym programem uruchamianym z terminala
i docelowo będzie działać bez interfejsu graficznego.

**Python odpowiada za obsługę eksperymentów i analizę**: uruchamianie silnika,
serie symulacji i opracowanie wyników. `uv` zarządza interpreterem,
środowiskiem `.venv` i zależnościami opisanymi w `pyproject.toml`.
Plik `uv.lock` przechowuje rozwiązane wersje zależności i należy go commitować.

Na początek Python komunikuje się z C++ przez uruchomienie procesu.
Docelowy kontrakt obejmuje scenariusz JSON na wejściu, jawne ziarno losowe
oraz pliki wynikowe CSV na wyjściu. Tego kontraktu silnik jeszcze nie implementuje.
Nie wymagamy obecnie wiązań C++/Python ani rozszerzenia kompilowanego dla Pythona.

CMake i Ninja są zależnościami grupy `dev` instalowanymi przez `uv`.
Kompilator C++ pozostaje narzędziem systemowym — `uv` go nie instaluje.
Dokumentacja: [zależności i grupy w uv](https://docs.astral.sh/uv/concepts/projects/dependencies/).

Conan będzie zarządzać zależnościami C++, a `uv` — środowiskiem i zależnościami
Pythona. CMake nadal odpowiada za konfigurację budowania, a Ninja za jego
wykonanie. Na obecnym etapie instalacja Conana nie jest wymagana.

## Struktura

```text
Warriors/
├── CMakeLists.txt
├── pyproject.toml         # konfiguracja środowiska Python i zależności
├── uv.lock                # zablokowane wersje zależności
├── .python-version        # domyślny interpreter dla uv
├── README.md
├── .gitignore
├── src/
│   ├── main.cpp           # punkt wejścia aplikacji
│   ├── simulation/        # świat, czas i aktualizacja stanu
│   ├── agents/            # żołnierze, oddziały i dowództwo
│   ├── movement/          # ruch, formacje i indeks przestrzenny
│   ├── combat/            # ostrzał, walka wręcz i straty
│   └── command/           # rozkazy, meldunki i koordynacja
├── scenarios/             # definicje scenariuszy i ich parametrów
├── analysis/              # skrypty Python do analizy i eksperymentów
├── tools/
│   └── dev.py             # budowanie i uruchamianie silnika przez uv
├── tests/                 # przyszłe testy mechanik i powtarzalności
└── docs/                  # założenia modelu i źródła historyczne
```

Puste katalogi zawierają `.gitkeep`, aby Git zachował strukturę.
Wyniki eksperymentów zapisujemy docelowo do `outputs/`, które Git ignoruje.

## Budowanie i uruchamianie

Wymagane są [uv](https://docs.astral.sh/uv/getting-started/installation/)
oraz systemowy kompilator C++20, np. GCC, Clang lub MSVC.
Na Windows z MSVC użyj terminala deweloperskiego Visual Studio.
Polecenia wykonaj w katalogu głównym repozytorium. CMake i Ninja zainstaluje `uv`:

```bash
uv sync --locked
uv run --locked python tools/dev.py build
uv run --locked python tools/dev.py run
```

Polecenie `run` najpierw buduje silnik. Domyślna konfiguracja to `Debug`.
Wersję do pomiarów wydajności uruchom przez:

```bash
uv run --locked python tools/dev.py run --config Release
```

Pliki budowania trafiają do `build/debug/` lub `build/release/`.
Każdy katalog zawiera również `compile_commands.json` dla narzędzi C++.
Aktywacja `.venv` nie jest konieczna, gdy używasz `uv run`.

Nowe biblioteki do analizy dodawaj przez `uv add nazwa-biblioteki`, a narzędzia
deweloperskie przez `uv add --dev nazwa-narzedzia`. Po zmianie zależności
commituj zarówno `pyproject.toml`, jak i `uv.lock`.

Skrypt analityczny można uruchomić przez `uv run python analysis/nazwa_skryptu.py`,
gdy zostanie dodany. Obecnie katalog `analysis/` jest pusty.

Testy nie są jeszcze skonfigurowane. Dodamy je wraz z pierwszymi mechanikami.

## Pierwszy etap implementacji

1. Stan świata, stały krok czasu i generator losowy z jawnym ziarnem.
2. Dwa oddziały piechoty i wyszukiwanie sąsiadów przez siatkę przestrzenną.
3. Ruch w formacji, ostrzał, przeładowanie i straty.
4. Wczytywanie parametrów scenariusza oraz zapis przebiegu do CSV.
5. Sprawdzenie powtarzalności i analiza wielu uruchomień.

Rdzeń powinien działać bez grafiki. Wizualizacja ma odczytywać stan symulacji
lub zapis jej przebiegu. Wszystkie wielkości fizyczne powinny mieć jawne
jednostki, a parametry historyczne — udokumentowane źródła lub oznaczenie
jako założenia. Zgodność zwycięzcy jednej bitwy nie wystarcza do walidacji.

## Literatura wyjściowa

- F. W. Lanchester (1916), *Aircraft in Warfare*,
  [rozdział V](https://en.wikisource.org/wiki/Aircraft_in_Warfare_(1916)/Chapter_5).
- A. Ilachinski (2004), *Artificial War: Multiagent-Based Simulation of Combat*,
  World Scientific — opis EINSTein.
- M. Waniek (2014), *Petro: A Multi-agent Model of Historical Warfare*,
  [PDF](https://www.mimuw.edu.pl/~vua/files/waniek2014petro.pdf).
- C. Scogings, K. Hawick (2012), *An Agent-Based Model of the Battle of Isandlwana*,
  [PDF](https://informs-sim.org/wsc12papers/includes/files/con269.pdf).
