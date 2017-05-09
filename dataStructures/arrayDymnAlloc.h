#ifndef arraydymnalloc_H
#define arraydymnalloc_H

int 		createArray				(ArrayDescriber *arrDesc);
void 		initializeArray			(ArrayDescriber *arrDesc);
int 		resizeArray				(ArrayDescriber *arrDesc, unsigned int newsize);
void 		addElementOnTop			(ArrayDescriber *arrDesc, Var elem);
Var 		removeElementOnTop		(ArrayDescriber *arrDesc);
Var 		getTopElement			(ArrayDescriber *arrDesc);
void 		setElement				(ArrayDescriber *arrDesc, Var elem, unsigned int position);
void 		printArrayInfo			(ArrayDescriber arrDesc);
void 		printArray				(ArrayDescriber arrDesc);
void 		printVar				(Var var, char dataType[3], int ident);

#endif
