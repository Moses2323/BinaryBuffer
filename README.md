Проект предоставляет два класса для удобной записи информации в бинарном виде:
BinaryBufferOutS для вывода в выбранный поток и BinaryBufferInS для вывода информации
из потока.

Классы при создании производят захват потока по ссылке и использует его методы .write() и .read() .
Запись и считывание производятся таким же образом, как и при работе с обычным потоком.
Для классов с непрерывным блоком хранения данных (std::vector, std::valarray, std::string)
написаны перегруженные версии операторов >> , << .

Схема использования:
```C++
std::ofstream fout;
fout.open("test.txt", std::ios::out | std::ios::binary);

int vi = 3434;
float vf = 34.3353;
double vd = 555444.34234234;
const char* cs = "Hello, world!";
std::string cpps = "I\'m prohibited person";
size_t N = 20;
std::vector<float> vecf(N);
std::valarray<double> vald(N);

for(size_t i=0; i < N; ++i){
	vecf[i] = i * 3.434;
	vald[i] = i * 99.232333;
}

BinaryBufferOutS binbuf(fout);
binbuf << vi << vf << vd << cs << cpps << vecf << vald;
binbuf.flushIt();

fout.close();
```

Строки в Си стиле (const char*) выводятся в поток без завершающего символа '\0'.
Строки в С++ стиле (std::string) также выводятся в поток без завершающего символа.
Все вектора (std::vector, std::valarray) записываются в файл подряд без разделительных символов.
