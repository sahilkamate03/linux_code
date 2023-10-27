import unittest
import file

class TestFile(unittest.TestCase):

	def test_add(self):
		result = file.add(10,5)
		self.assertEqual(result, 1)

if __name__ == '__main__':
	unittest.main()