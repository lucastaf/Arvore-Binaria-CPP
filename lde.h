#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <string>

template <class tipoInfo>
struct No
{
	tipoInfo info;
	No<tipoInfo> *eloA = nullptr;
	No<tipoInfo> *eloF = nullptr;
};

template <class tipoItem>
class LDE
{
	No<tipoItem> *comeco = nullptr;
	No<tipoItem> *fim = nullptr;

protected:
	No<tipoItem> *getNo(int id)
	{
		if (this->comeco == nullptr)
		{
			return nullptr;
		}
		No<tipoItem> *aux = this->comeco;
		if (id >= 0)
		{
			for (int i = 0; i < id; i++)
			{
				aux = aux->eloF;
				if (aux == nullptr)
				{
					aux = this->comeco;
				}
			}
		}
		else
		{
			for (int i = 0; i > id; i--)
			{
				aux = aux->eloA;
				if (aux == nullptr)
				{
					aux = this->fim;
				}
			}
		}
		return aux;
	}

public:
	// Get
	tipoItem getItem(int id)
	{
		No<tipoItem> *aux = this->getNo(id);
		if (aux == nullptr)
		{
			tipoItem novoItem;
			return novoItem;
		}
		return aux->info;
	}

	int getIndex(tipoItem item)
	{
		No<tipoItem> *aux = this->comeco;
		int count = 0;
		while (aux != nullptr)
		{
			if (aux->info == item)
			{
				return count;
			}
			count++;
			aux = aux->eloF;
		}
		return -1;
	}

	int getLength()
	{
		int count = 0;
		No<tipoItem> *aux = this->comeco;
		while (aux != nullptr)
		{
			aux = aux->eloF;
			count++;
		}
		return count;
	}

	// Edit
	void editItem(tipoItem procura, tipoItem novo)
	{
		No<tipoItem> *aux = this->comeco;
		while (aux != nullptr)
		{
			if (aux->info == procura)
			{
				aux->info = novo;
				return;
			}
			aux = aux->eloF;
		}
	}

	void editItemById(int procura, tipoItem novo)
	{
		No<tipoItem> *aux = this->getNo(procura);
		aux->info = novo;
	}

	// Add
	void push(tipoItem info)
	{
		No<tipoItem> *novoNovo = new No<tipoItem>;
		novoNovo->info = info;
		if (this->comeco == nullptr)
		{
			this->comeco = novoNovo;
			this->fim = novoNovo;
		}
		else
		{
			this->fim->eloF = novoNovo;
			novoNovo->eloA = this->fim;
			this->fim = novoNovo;
		}
	}

	void insert(int index, tipoItem info)
	{
		No<tipoItem> *novoItem = new No<tipoItem>;
		novoItem->info = info;
		if (this->comeco == nullptr)
		{
			this->comeco = novoItem;
			this->fim = novoItem;
		}
		No<tipoItem> *aux = this->getNo(index);

		No<tipoItem> *eloAnterior = aux->eloA;
		aux->eloA = novoItem;
		novoItem->eloF = aux;
		if (eloAnterior != nullptr)
		{
			novoItem->eloA = eloAnterior;
			eloAnterior->eloF = novoItem;
		}
		else
		{
			this->comeco = novoItem;
		}
	}

	void append(LDE lista)
	{
		No<tipoItem> *aux = lista.getNo(0);
		while (aux != nullptr)
		{
			this->push(aux->info);
			aux = aux->eloF;
		}
	}

	void copy(LDE lista)
	{
		this->deleteList();
		this->append(lista);
	}

	// Delete
	void pop()
	{
		No<tipoItem> *ultimoItem = this->fim;
		if (ultimoItem == nullptr)
		{
			return;
		}
		if (ultimoItem->eloA != nullptr)
		{
			ultimoItem->eloA->eloF = nullptr;
		}
		else
		{
			this->comeco = nullptr;
		}
		this->fim = ultimoItem->eloA;
		delete ultimoItem;
	}

	void deleteList()
	{
		No<tipoItem> *prox = this->comeco;
		while (prox != nullptr)
		{
			No<tipoItem> *deletedNo = prox;
			prox = prox->eloF;
			delete deletedNo;
		}
		this->comeco = nullptr;
		this->fim = nullptr;
	}

	void deleteItem(tipoItem item)
	{
		if (this->comeco == nullptr)
		{
			return;
		}
		No<tipoItem> *aux = this->comeco;
		while (aux != nullptr)
		{
			if (aux->info == item)
			{
				No<tipoItem> *AntElo = aux->eloA;
				No<tipoItem> *ProxElo = aux->eloF;

				if (ProxElo == nullptr)
				{
					AntElo->eloF = nullptr;
					this->fim = AntElo;
				}
				else if (AntElo == nullptr)
				{
					ProxElo->eloA = nullptr;
					this->comeco = ProxElo;
				}
				else
				{
					AntElo->eloF = ProxElo;
					ProxElo->eloA = AntElo;
				}
				delete aux;
			}
		}
	}

	void deleteItemById(int id)
	{
		if (this->comeco == nullptr)
		{
			return;
		}
		No<tipoItem> *aux = this->getNo(id);
		No<tipoItem> *AntElo = aux->eloA;
		No<tipoItem> *ProxElo = aux->eloF;

		if (ProxElo == nullptr && AntElo == nullptr)
		{
			this->comeco = nullptr;
			this->fim = nullptr;
		}
		else if (ProxElo == nullptr)
		{
			AntElo->eloF = nullptr;
			this->fim = AntElo;
		}
		else if (AntElo == nullptr)
		{
			ProxElo->eloA = nullptr;
			this->comeco = ProxElo;
		}
		else
		{
			AntElo->eloF = ProxElo;
			ProxElo->eloA = AntElo;
		}
		delete aux;
	}

	// Misc
	void print()
	{
		std::cout << '[';
		No<tipoItem> *aux = this->comeco;
		while (aux != nullptr)
		{
			std::cout << aux->info << ",";
			aux = aux->eloF;
		}
		std::cout << "] \n";
	}
};