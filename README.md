# Вариант 17.

Написать программу, выполняющую разбиение неориентированного графа на две равные по количеству вершин части.

Разбиение должно выполняться опираясь на следующие действия:
  Первой вершиной части 1 и первой вершиной части 2 берутся две случайные вершины, не соединенные ребром
    (если таких нет, то это полный граф и тогда не важно какие вершины попадут в какую часть).
  Поочередно к каждой из частей добавляется вершина, для которой наибольшим является количество ребер,
  соединяющих ее с вершинами, уже набранными в эту часть.
  
Особенности программы: 
  Язык – C++;
  граф представлен матрицей смежностей и хранится в файле input.txt (новая строка матрицы – новая строка файла);
  в файл result.txt записывается число, являющееся количеством дуг, идущих из одной части графа в другую (в первой строке)
    и наборы вершин, относящиеся к первой и второй части разбиения (вторая строка – вершины графа, относящиеся к части 1 разбиения,
    третья строка – вершины графа, относящиеся части 2 разбиения).
