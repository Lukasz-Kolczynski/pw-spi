// fun foo(a: Int, b: Int, c: Int)
// {
//     println("a=$a, b=$b, c=$c")
// }

// fun main()
// {
//     foo(a=3,c=5,b=7)
// }

// -------------------------------------------------------

// fun main()
// {
// val waterFilter = {level: Int -> level / 2}
// val a = {level: Int -> level / 2}

// waterFilter = a
// var dirtLevel = 20

// println(waterFilter)
// println(waterFilter(dirtLevel))

// }


// data class User(val name: String, val age: Int)

// val user = User("Alice", 25)

// fun main()
// {
// println(user) 
// }

// -------------------------------------------------------

data class WordEntry
(
    val word : String,
    val choices : List<String>,
    val correctLetter : String,
    var totalAnswers : Int,
    var correctAnswers : Int
)

val words = mutableListOf(
    WordEntry("p?ygoda", listOf("sz", "rz", "ż"), "rz", 12, 6),
    WordEntry("d?emią", listOf("rz", "ż"), "ż", 8, 3),
    WordEntry("mo?e", listOf("r", "ż"), "r", 10, 5)
)


fun main(args: Array<String>)
{
    if(args.isEmpty())
    {
        println("Wrong amount of words")
        return 
    }
    var amount: Int = args[0].toInt()
    if (amount > words.size)
    {
        println("Is only ${words.size} words. Selected ${words.size}.")
        amount = words.size
    }

}




