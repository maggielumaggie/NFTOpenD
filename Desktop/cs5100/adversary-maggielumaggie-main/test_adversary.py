import adversary as ad
import networkx as nx
import generator as gen


class TestAdversary:
    """
    Autograder - *DO NOT* alter this file
    It tests if your functions are working as expected.
    """
    empty = nx.Graph()

    # def test_minimax(self):
    #     """
    #     Tests Minimax
    #     """
    #     assert callable(getattr(ad, 'minimax')), "minimax function not defined"
    #     example = gen.exampleGameTree()
    #     value = ad.minimax(example)
    #     assert isinstance(value, int), "should return a number"
    #     assert value == 3, "example tree should result in 3"
    #     result = ad.minimax(self.empty)
    #     assert result == None, "empty tree should return None"

    def test_alphabeta(self):
        """
        Tests AlphaBeta
        """
        assert callable(getattr(ad, 'alphabeta')), "alphabeta function not defined"
        example = gen.exampleGameTree()
        result = ad.alphabeta(example)
        assert isinstance(result, nx.Graph), "should return a graph"
        answer = gen.exampleGameTree()
        answer.remove_edge("C","c2")
        answer.remove_edge("C","c3")
        answer.remove_edge("D", "d1")
        answer.remove_edge("D", "d2")
        resultedges = nx.traversal.bfs_tree(result,"A").edges()
        answeredges = nx.traversal.bfs_tree(answer,"A").edges()
        assert resultedges == answeredges, "example tree should result in " + str(answeredges) + " instead of " + str(resultedges)
        result = ad.minimax(self.empty)
        assert result == None, "empty tree should return None"