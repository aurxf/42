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

template<typename C, typename Iterator>
void	FordJohnson::push_sorted(struct LocalVariables<Iterator>& lv, C& unsorted, C& container)
{
	for (int i = lv.size_to_insert; i > 0; i--)
	{
		lv.index_to_insert = container.insert(lv.index_to_insert, *lv.it);
		lv.it = unsorted.erase(lv.it);
		lv.it--;	
	}
	lv.index_to_insert = container.insert(lv.index_to_insert, *lv.it);
	lv.it = unsorted.erase(lv.it);
	if (unsorted.empty() == false)
		lv.it = unsorted.erase(lv.it);

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
void	FordJohnson::init_variables(struct LocalVariables<Iterator>& lv, C& unsorted, const int& size_comparison)
{
	int	i_jacobsthal = this->index_jacobsthal(lv.n);
	int	size_elements = (size_comparison / 2 + 1);
	int	modulo = 0;

	lv.it = unsorted.begin();
	if ((unsorted.size() % size_elements) != 0)
		modulo = 1;
	if (((static_cast<int>(unsorted.size()) / size_elements) + modulo) < i_jacobsthal)
	{
		lv.n = 2;
		i_jacobsthal = 1;
	}
	lv.it += (size_elements * (i_jacobsthal - 1 - lv.already_insert));
	if (std::distance(lv.it, unsorted.end()) < size_elements)
	{
		lv.nb_link = -1;
		lv.to_insert = *(unsorted.end() - 1);
		lv.size_to_insert = static_cast<int>(std::distance(lv.it, unsorted.end())) - 1;
		lv.it = unsorted.end() - 1;
	}
	else
	{
		lv.nb_link = *(lv.it + size_elements - 1);
		lv.to_insert = *(lv.it + size_elements - 2);
		lv.size_to_insert = size_elements - 2;
		lv.it += size_elements - 2;
	}
}

template <typename C>
void	FordJohnson::manage_unsorted(C& container, C& unsorted, const int& size_comparison)
{
	LocalVariables<typename C::iterator>	lv;

	lv.n = 2;
	lv.already_insert = 0;	
	while (unsorted.empty() == false)
	{
		this->init_variables(lv, unsorted, size_comparison);	
		lv.index_to_insert = this->binary_search(container, lv.nb_link, lv.to_insert, size_comparison);
		this->push_sorted(lv, unsorted, container);
		lv.already_insert++;
		lv.n++;
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
		this->manage_unsorted(container, unsorted, size_comparison);
		unsorted.clear();
		size_comparison /= 2;
	}
}
