#include "FordJohnson.hpp"

template<typename C>
void	FordJohnson::sort_odd(C& container, const int& size_comparison)
{
	for (typename C::iterator it = container.begin(); it != container.end(); it += size_comparison)
	{
		if (std::distance(container.begin(), it) + size_comparison > static_cast<int>(container.size()))
			break;
		if (*(it + (size_comparison / 2) - 1) > *(it + size_comparison - 1))
			std::swap_ranges(it, it + (size_comparison / 2), it + (size_comparison / 2));
	}
}

template<typename C>
void	FordJohnson::push_unsorted(C& container, C& unsorted, const int& size_comparison)
{
	for (typename C::iterator	it = container.begin() + size_comparison; it != container.end(); it += size_comparison / 2)
	{
		if (std::distance(container.begin(), it) + (size_comparison / 2) > static_cast<int>(container.size()))
			break;
		for (int i = 0; i < (size_comparison / 2); i++)
		{
			unsorted.push_back(*it);
			it = container.erase(it);
		}
		if (it != container.end())
			unsorted.push_back(*it);
	}
}

template<typename C>
typename C::iterator	FordJohnson::binary_search(C& container, const int& nb_link, const int& to_insert, const int& size_comparison)
{
	typename C::iterator	link = std::find(container.begin(), container.end(), nb_link);
	typename C::iterator	i_binary = link - 1 - (link - 1 - container.begin()) / 2;
	int			half_distance = (link - i_binary) / 2 / size_comparison;

	if (half_distance < 1 || size_comparison == 2)
		half_distance = 1;
	while (1)
	{
		if (i_binary >= link)
			break;
		if (i_binary != container.begin() && to_insert < *(i_binary + (size_comparison / 2 - 1)) && to_insert > *(i_binary - 1))
			break;
		if (i_binary == container.begin() && to_insert < *(i_binary + (size_comparison / 2 - 1)))
			break;
		if (to_insert > *(i_binary + (size_comparison / 2 - 1)))
			i_binary += (half_distance * (size_comparison / 2));
		else
			i_binary -= (half_distance * (size_comparison / 2));
		if (half_distance > 1)
			half_distance /= 2;	
	}
	return i_binary;
}

template <typename C, typename Iterator>
void	FordJohnson::init_variables(struct LocalVariables<Iterator>& lc, C& unsorted, const int& size_comparison)
{
	if (static_cast<int>(unsorted.size()) < (size_comparison / 2 + 1))
	{

		lc.it = unsorted.end() - 1;
		lc.nb_link = -1;
		lc.to_insert = *(unsorted.end() - 1);
		lc.size_to_insert = static_cast<int>(unsorted.size()) - 1;
	}
	else
	{
		int	i_jacobsthal = this->index_jacobsthal(lc.i_while);

		if (static_cast<int>(unsorted.size()) / (size_comparison / 2 + 1) < i_jacobsthal)
		{
			lc.i_while = 1;
			i_jacobsthal = this->index_jacobsthal(lc.i_while);	
		}
		std::cout << "jacosthal = " << i_jacobsthal << std::endl;
		std::cout << "unsorted.size = " << static_cast<int>(unsorted.size()) << std::endl;
		lc.it = unsorted.begin();
		lc.it += (size_comparison / 2 + 1) * i_jacobsthal;
		lc.nb_link = *(unsorted.begin() + (size_comparison / 2));
		lc.to_insert = *(unsorted.begin() + (size_comparison / 2 - 1));
		lc.size_to_insert = size_comparison / 2 - 1;
	}
}

template <typename C>
void	FordJohnson::insert_sorted(C& container, C& unsorted, const int& size_comparison)
{
	LocalVariables<typename C::iterator>	lc;

	lc.i_while = 1;	
	while (unsorted.empty() == false)
	{
		this->init_variables(lc, unsorted, size_comparison);
		lc.index_to_insert = this->binary_search(container, lc.nb_link, lc.to_insert, size_comparison);
		for (int i = lc.size_to_insert; i > 0; i--)
		{
			lc.index_to_insert = container.insert(lc.index_to_insert, *lc.it);
			lc.it = unsorted.erase(lc.it);
			lc.it--;	
		}
		lc.index_to_insert = container.insert(lc.index_to_insert, *lc.it);
		lc.it = unsorted.erase(lc.it);
		if (unsorted.empty() == false)
			lc.it = unsorted.erase(lc.it);
		lc.i_while++;
	}
}

template <typename C>
void	FordJohnson::sort(C& container)
{
	C	unsorted;	
	int	size_comparison = 2;

	while (size_comparison <= static_cast<int>(container.size()))
	{
		this->sort_odd(container, size_comparison);
		size_comparison *= 2;
	}
	while (size_comparison >= 2)
	{
		this->push_unsorted(container, unsorted, size_comparison);
		this->insert_sorted(container, unsorted, size_comparison);
		unsorted.clear();
		size_comparison /= 2;
	}
}
