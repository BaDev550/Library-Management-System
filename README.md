# Library-Management-System

---

I made this to learn a bit more about a C++ file management system. Basically, there’s a default user named "Admin" with the password "1234," but you can change that from the `users.txt` file. You can register new users if you’re an admin, you can adjust their roles. I was gonna port it over from my banking project, but I was just too lazy, lol.

Anyway, whenever you register a new user, it saves the data in this template:

```
USER,[USERNAME],[PASSWORD],[RANK]
```

Everything that starts with `BOOK,` represents the user's books. For example:

```
BOOK,Kürk Mantolu Madonna,Sabahattin Ali,0
```

The last `0` shows whether the user has that book or not.

`ENDUSER` marks the end of that user's data.

Here’s how it looks in the file:

```
USER,Admin,1234,1
BOOK,Kürk Mantolu Madonna,Sabahattin Ali,0
BOOK,1984,George Orwell,0
ENDUSER
```

That’s how the admin's data is saved and used.

--- 
