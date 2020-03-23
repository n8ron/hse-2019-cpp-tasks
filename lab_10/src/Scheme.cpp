#include <cstdio>
#include <assert.h>
#include "Scheme.hpp"

Scheme::Scheme(int capacity) {
	assert(capacity > 0);
    figures_ = new Figure*[capacity];
    size_ = 0;
} 

Scheme::~Scheme() {
    for (int i = 0; i < size_; i++) {
        delete figures_[i];
    }
    delete [] figures_;
}

int Scheme::get_index(int id) {
    for (int i = 0; i < size_; i++) {
        if (figures_[i]->get_id() == id) {
            return i;
        } 
    }
    return -1;
}

void Scheme::move(int id, int new_x, int new_y) {
	int index = get_index(id); 
    if (index == -1) {
         printf("ERROR: wrong ID");
         return;
    }
    figures_[index]->move(new_x, new_y);
}

void Scheme::push_back_figure(Figure* fg) {
    assert(fg != nullptr);
    figures_[size_++] = fg;
}

void Scheme::zoom_figure(int id, int factor) {
	int index = get_index(id);
	if (index == -1) {
         printf("ERROR: wrong ID\n");
         return;
    }
    figures_[index]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y) {
	for (int i = 0; i < size_; i++) {
		if (figures_[i]->is_inside(x, y)) {
			return figures_[i];
		}
	}
	return nullptr;
}

void Scheme::remove_figure(int id) {
	int index = get_index(id); 
    if (index == -1) {
         printf("ERROR: wrong ID\n");
         return;
    }
    delete figures_[index];
    for (int i = index; i < size_; i++) {
    	figures_[i] = figures_[i + 1];
    }
    --size_;
}

void Scheme::print_all_figures() {
	for (int i = 0; i < size_; i++) {
		figures_[i]->print();
	}
}