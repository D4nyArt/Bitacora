Una bitácora es un repositorio que permite llevar registro de eventos relacionados con alguna situación específica, como por ejemplo, 
el registro de visitantes de un museo, la bitácora de navegación de un barco, el log de eventos de un servidor o sistema de red, entre otros. 
Hay bitácoras que pueden tener un tamaño máximo de eventos a registrar (un cuaderno, por ejemplo); como también pueden haber bitácoras con un 
número "ilimitado" de eventos (dependiendo de la capacidad del repositorio donde éstos serán almacenados).

Desde el punto de vista general, una bitácora está asociada a un conjunto de campos (generalmente son cadenas de caracteres) cada uno de los 
cuales tiene que ver con alguno de los datos del evento (por ejemplo, fecha, nombre, descripción, código de error, etc.). En otras palabras, 
cada bitácora tiene su propia especificación de campos y, una vez establecida esta asociación, la bitácora se mantiene fija para poder almacenar 
el tipo particular de eventos que representan esos campos.

Como estructura de datos, la bitácora permite realizar operaciones de ingreso y consulta de eventos, así como también la limpieza de los mismos. 
No existe una operación de eliminación parcial de eventos. En relación al ingreso, los eventos se pueden ingresar de dos maneras: individualmente 
y por lote. En cualquiera de los dos casos, los datos del evento deben coincidir con la lista de campos establecidos en tiempo de definición de la 
bitácora. Nótese que el orden es importante para tener una correspondencia válida entre el conjunto de campos definidos y el conjunto de datos de 
un evento que se desea agregar. Por ejemplo, si los campos del evento son las cadenas A, B y C, un evento válido puede ser "algo relativo a A", 
"algo relativo a B", "algo relativo a C". En el ingreso por lote los eventos son cargados desde un archivo cuyo nombre es indicado como parámetro en 
la función. En caso de que la bitácora sea de tamaño limitado, las operaciones de ingreso no se podrán realizar. Funciones para saber si una bitácora 
está llena o vacía son de interés para este caso. 

Las operaciones de consulta se realizan basado en la búsqueda de eventos, que corresponden a una clave previamente indicada al momento de definir los 
campos de la bitácora. Uno de los campos debe ser designado como clave de búsqueda. Por ejemplo, para el caso de las cadenas A, B, C, si selecciona A 
como clave, las consultas de los eventos de la bitácora se regirán por este campo. 

Para acelerar la búsqueda, una función de ordenamiento permitirá ordenar los eventos que están actualmente guardados en la bitácora. Como resultado de
esta operación, los eventos ordenados se deben guardar en un archivo cuyo nombre debe ser indicado por el usuario en el momento de la llamada de la función.
