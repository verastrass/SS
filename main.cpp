#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <time.h>

using std::vector;
using std::fstream;
using std::stringstream;
using std::endl;
using std::string;
using std::set;

const string INPUT_FILE_NAME = "input.txt";
const string OUTPUT_FILE_NAME = "result.txt";

int numberOfVertices;
vector<vector<int>> adjMatrix;
set<int> setOfVertices1;
set<int> setOfVertices2;


bool isSymmetricMatrix() {
	for (int i = 0; i < numberOfVertices; ++i)
		for (int j = 0; j < numberOfVertices; ++j)
			if (adjMatrix[i][j] != adjMatrix[j][i])
				return false;
	return true;
}


string read() {
	int v;
	string firstString, msg = "";
	fstream fin(INPUT_FILE_NAME, fstream::in);

	// computing number of vertices from the information in the first line of file
	getline(fin, firstString);
	stringstream ss(firstString, stringstream::in);
	adjMatrix.resize(1);
	while (ss >> v)
		adjMatrix[0].push_back(v);

	numberOfVertices = adjMatrix[0].size();
	if (numberOfVertices > 0 && !(numberOfVertices % 2))
	{
		adjMatrix.resize(numberOfVertices);
		for (int i = 1; i < numberOfVertices; ++i)
		{
			adjMatrix[i].resize(numberOfVertices);
			for (int j = 0; j < numberOfVertices; ++j)
			{
				fin >> v;
				adjMatrix[i][j] = v;
			}
		}

		if (!isSymmetricMatrix())
			msg = "Adjacency matrix must be symmetric";
	}
	else
		msg = "Number of vertices must be positive and even";

	fin.close();
	return msg;
}


void write(const string& msg) {
	fstream fout(OUTPUT_FILE_NAME, fstream::out);
	
	if (msg.empty())
	{
		int amountOfEdges = 0;
		for (auto& v : setOfVertices1)
			for (auto& u : setOfVertices2)
				if (adjMatrix[v][u])
					++amountOfEdges;

		fout << amountOfEdges << endl;

		for (auto& v : setOfVertices1)
			fout << v << ' ';
		fout << endl;

		for (auto& v : setOfVertices2)
			fout << v << ' ';
	}
	else
		fout << msg;
	
	fout.close();
}


int chooseNextVertex(const set<int>& vacantVertices, const set<int>& choosedVertices) {
	int curAmountOfEdges, maxAmountOfEdges = 0;
	int maxV = *vacantVertices.begin();

	for (auto& v : vacantVertices)
	{
		curAmountOfEdges = 0;
		for (auto& u : choosedVertices)
			if (adjMatrix[v][u])
				++curAmountOfEdges;
		
		if (curAmountOfEdges > maxAmountOfEdges)
		{
			maxAmountOfEdges = curAmountOfEdges;
			maxV = v;
		}
	}

	return maxV;
}


void splitIntoTwoSets() {
	srand(time(NULL));
	set<int> firstRandomVertexSet;
	set<int> secondRandomVertexSet;
	for (int i = 0; i < numberOfVertices; ++i)
		firstRandomVertexSet.insert(i);

	while (true)
	{
		// spliting vertices into two sets, if could not choose two first random unconnected vertices
		if (firstRandomVertexSet.empty())
		{
			auto n2 = numberOfVertices / 2;
			for (int i = 0; i < n2; ++i)
			{
				setOfVertices1.insert(i);
				setOfVertices2.insert(i + n2);
			}
			return;
		}

		// choosing the first random vertex
		set<int>::const_iterator it1(firstRandomVertexSet.begin());
		advance(it1, rand() % firstRandomVertexSet.size());
		auto firstRandomVertex = *it1;

		// constructing set of vertices, which are not unconnected to the first choosed vertex
		for (int i = 0; i < numberOfVertices; ++i)
			if (i != firstRandomVertex && !adjMatrix[firstRandomVertex][i])
				secondRandomVertexSet.insert(i);

		// choosing the second random vertex, if constructed set is not empty
		if (!secondRandomVertexSet.empty())
		{
			setOfVertices1.insert(firstRandomVertex);
			set<int>::const_iterator it2(secondRandomVertexSet.begin());
			advance(it2, rand() % secondRandomVertexSet.size());
			setOfVertices2.insert(*it2);
			break;
		}

		// removing inappropriate vertex
		firstRandomVertexSet.erase(it1);
		secondRandomVertexSet.clear();
	}

	// constructing set of vacant vertices 
	set<int> vacantVertices;
	for (int i = 0; i < numberOfVertices; ++i)
		vacantVertices.insert(i);

	vacantVertices.erase(*setOfVertices1.begin());
	vacantVertices.erase(*setOfVertices2.begin());

	// spliting vacant vertices
	while (!vacantVertices.empty())
	{
		auto v = chooseNextVertex(vacantVertices, setOfVertices1);
		setOfVertices1.insert(v);
		vacantVertices.erase(v);

		v = chooseNextVertex(vacantVertices, setOfVertices2);
		setOfVertices2.insert(v);
		vacantVertices.erase(v);
	}
}


int main() {
	auto msg = read();
	if (msg.empty())
		splitIntoTwoSets();
	
	write(msg);
	return EXIT_SUCCESS;
}
